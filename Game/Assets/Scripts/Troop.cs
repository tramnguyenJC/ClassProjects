using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public abstract class Troop : MonoBehaviour
{
		
	// The BoxCollider2D component attached to this object.
	protected BoxCollider2D boxCollider;
	//The Rigidbody2D component attached to this object.
	protected Rigidbody2D rb2D;
	// Maximum health units the Troop has
	protected int maxHealth;
	// Current health units the Troop has
	public int currentHealth;
	// Damage power of each attack
	protected int damagePower;
 	// Movement vector of Troop, horizontally
	protected Vector2 movement_vector;
	// Speed of movement
	public float speed;
	// True if is in fighting stage.
	protected bool isFighting;
	// True if in collision with Character of same type and is thus waiting
	// until the other Character is moving
	protected bool isWaiting;

	// Identifier (for debugging purposes)
	protected int id;

	public void setId (int _id) {
		id = _id;
	}

	public int getId () {
		return id;
	}

	// Variables related to Health Bar
	// Ratio of the Health bar's width versus the maximum health
	private float ratioHealthBarSizeToHealth;
	// Rectangle representing the health bar.
	public RectTransform healthBar;
		
	protected virtual void Start ()
	{
		// Get a component reference to this object's BoxCollider2D
		boxCollider = GetComponent <BoxCollider2D> ();
			
		// Get a component reference to this object's Rigidbody2D
		rb2D = GetComponent <Rigidbody2D> ();

		// Set currentHealth to maxHealth;
		currentHealth = maxHealth;

		// Troop starts out not in fighting or waiting state.
		isFighting = false;
		isWaiting = false;

		ratioHealthBarSizeToHealth = healthBar.sizeDelta.x/maxHealth;

	}
		
	public void ReceiveDamage(int damage) {
		// Current health units decrease accordingly.
		currentHealth -= damage;

		// If health units is less than or equal to zero, the Troop dies,
		// and the GameObject is destroyed.
		if (currentHealth <= 0) {
			Destroy (gameObject);
		}
		// Update size of Health bar
		healthBar.sizeDelta = new Vector2(
			currentHealth * ratioHealthBarSizeToHealth, healthBar.sizeDelta.y);
	}

	// Move the Character in the intended direction.
	protected void Move() {
		rb2D.MovePosition(rb2D.position + 
    		speed*movement_vector * Time.deltaTime);
	}

	// The abstract modifier indicates that the thing being modified has a
	// missing or incomplete implementation. OnTriggerEnter2D will be overriden
	// by functions in the inheriting classes.
	protected abstract void OnTriggerEnter2D (Collider2D other);
	protected abstract void OnTriggerExit2D (Collider2D other);
}
