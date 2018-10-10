using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BadBase : BaseBehavior {

    // Use this for initialization
    protected override void Start()
    {
        // Set maximum health.
        maxHealth = 5;
        base.Start();
    }

    protected override void OnTriggerEnter2D(Collider2D other)
    {
        // Check if the tag of the trigger collided with is GoodTroop.
        if (other.tag == "GoodTroop")
        {
            currentHealth -= 1; // Each enemy troop does one damage
            Destroy(other.gameObject);  // Destroy the Troop game object
        }
        healthBar.sizeDelta = new Vector2(
            currentHealth * ratioHealthBarSizeToHealth, healthBar.sizeDelta.y);
    }
}
