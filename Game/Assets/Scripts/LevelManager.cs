using System.Collections;
using System;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class LevelManager : MonoBehaviour
{

    private Transform boardHolder;  // Child the boards we gen to boardHolder so we can collapse in hierarchy
                                    // Seems like we're using Transform just to do the hierarchy shit

    public GameObject background;
    public GameObject playerArrow;
    public GameObject badBase;
    public GameObject goodBase;
    public GameObject enemyGenerator;

    public void SetupScene()
    {
        Instantiate(background);
        Instantiate(badBase);
        Instantiate(goodBase);
        Instantiate(playerArrow);
        Instantiate(enemyGenerator);
    }
}
