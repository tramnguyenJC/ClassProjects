using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BaseBehavior : MonoBehaviour {

    // The BoxCollider2D component attached to this object.
    protected BoxCollider2D boxCollider;
    // Maximum health units the Base has
    protected int maxHealth;
    // Current health units the Base has
    protected int currentHealth;
    // Damage power of each attack
    protected int damagePower;

    // Variables related to Health Bar
    // Ratio of the Health bar's width versus the maximum health
    protected float ratioHealthBarSizeToHealth;
    // Rectangle representing the health bar.
    public RectTransform healthBar;

    protected virtual void Start()
    {
        // Get a component reference to this object's BoxCollider2D
        boxCollider = GetComponent<BoxCollider2D>();

        // Set currentHealth to maxHealth;
        currentHealth = maxHealth;

        ratioHealthBarSizeToHealth = healthBar.sizeDelta.x / maxHealth;
    }

    // The abstract modifier indicates that the thing being modified has a
    // missing or incomplete implementation. OnTriggerEnter2D will be overriden
    // by functions in the inheriting classes.
    protected abstract void OnTriggerEnter2D(Collider2D other);
}
