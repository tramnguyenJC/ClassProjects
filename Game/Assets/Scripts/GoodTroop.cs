using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoodTroop : Troop {
	// Reference to the Animator Component of this GoodTroop.
	public Animator animator;

	// Reference to the BadTroop the GoodTroop is attacking.
	public BadTroop opponent;

	// Use this for initialization
	protected override void Start () {
		// Get a component reference to the GoodTroop's animator component
		animator = gameObject.GetComponent<Animator>();

		// Set the GoodTroop to be moving rightwards.
		movement_vector = new Vector2(1,0);

		// Set maxHealth of the GoodTroop to 5
		maxHealth = 5;

		damagePower = 1;

		// Call the Start function of the Troop base class.
		base.Start();
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		if (!isFighting && !isWaiting)
		{
			Move();
		}
	}

	// Animation Events called to deliver damage to Opponent at the end of each
	// Fighting Animation loop.
	void FightOpponent() {
		if (isFighting) {
			opponent.ReceiveDamage(damagePower);
		}
	}


	protected override void OnTriggerEnter2D (Collider2D other)
	{
		// Check if the tag of the trigger collided with is BadTroop.
		if (other.tag == "BadTroop" && opponent == null)
		{
			// Set opponent to be the BadTroop collided with.
			opponent = other.gameObject.GetComponent<BadTroop>();

			// Need to first reset it to GoodTroopWalk, otherwise there's the
			// bug that after the Enemy kills this troop, the next Troop cannot
			// continue to damange the Enemy.
			// Then set the Fight trigger of the GoodTroop's animation
			// controller to play the GoodTroop's fighting animation.
			animator.ResetTrigger("GoodTroopWalk");
			animator.SetTrigger ("GoodTroopFight");
			
			isFighting = true;

		} else if (other.tag == "GoodTroop") {
			// If collided with another GoodTroop, whichever GoodTroop is
			// further forward (to the right) has priority to move, while the
			// one behind waits.
			if (other.gameObject.transform.position.x > transform.position.x) {
				isWaiting = true;
			}
		}
	}

	protected override void OnTriggerExit2D(Collider2D other)
    {
        // Set the walk trigger of the GoodTroop's animation controller in
		// order to play the GoodTroop's walking animation.
		animator.ResetTrigger("GoodTroopWalk");
		animator.SetTrigger ("GoodTroopWalk");

		// Reset all parameters
		isFighting = false;
		isWaiting = false;
		opponent = null;
		
		// @TODO (Add coins gained from killing the BadTroop).
    }
}