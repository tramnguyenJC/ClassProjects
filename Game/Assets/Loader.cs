using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Will check if Game Manager has been instantiated, and if not Instantiate() one from our prefab
// We'll add this script as a component for MainCamera since that always starts first
// We'll drag and drop our GameManager prefab as the public var
public class Loader : MonoBehaviour
{ 
    public GameObject gameManager;

    // Use this for initialization
    void Awake()
    {
        if (GameManager.instance == null)
            Instantiate(gameManager);
    }
}
