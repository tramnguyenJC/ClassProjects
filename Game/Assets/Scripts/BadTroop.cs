using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BadTroop : Troop {

	// Reference to the Animator Component of this BadTroop.
	public Animator animator;

	// Reference to the GoodTroop the Enemey is attacking.
	public GoodTroop opponent;

	// Use this for initialization
	protected override void Start () {
		// Get a component reference to the BadTroop's animator component
		animator = gameObject.GetComponent<Animator>();

		// Set the BadTroop to be moving leftwards.
		movement_vector = new Vector2(-1,0);

		// Set maximum health.
		maxHealth = 8;

		// Set damage power
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
		// Check if the tag of the trigger collided with is GoodTroop.
		if (other.tag == "GoodTroop" && opponent == null)
		{
			// Set opponent to equal the component passed in as a parameter.
			opponent = other.gameObject.GetComponent<GoodTroop>();
			
			
			// Set the attack trigger of the BadTroop's animation controller in
			// order to play the BadTroop's attack animation.
			animator.ResetTrigger ("BadTroopWalk");
			animator.SetTrigger ("BadTroopFight");

			// Set isFighting to true, indicates BadTroop is in fighting state
			isFighting = true;
			
		} else if (other.tag == "BadTroop" && opponent == null) {
			// If collided with another BadTroop, whichever BadTroop is
			// further forward (to the left) has priority to move, while the
			// one behind waits.
			if (other.gameObject.transform.position.x < transform.position.x) {
				isWaiting = true;
			}
		}
	}

	protected override void OnTriggerExit2D(Collider2D other)
    {
        // Set the walk trigger of the BadTroop's animation controller in
		// order to play the BadTroop's walking animation.
		animator.ResetTrigger ("BadTroopWalk");
		animator.SetTrigger ("BadTroopWalk");

		// Reset parameters
		isFighting = false;
		isWaiting = false;
		opponent = null;
    }
}
