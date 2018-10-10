using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{

    public static GameManager instance = null;
    private LevelManager levelManager;
    //[HideInInspector] public bool playersTurn = true;

    //private int level = 3;    // Used as a var to determine difficulty

    // Use this for initialization
    // Awake is called first as soon as object has been initialized by Unity, even if
    // the object has not been enabled (hasn't been rendered or updated)
    // Start is called after the object is enabled
    void Awake()
    {
        if (instance == null)
            instance = this;
        else if (instance != this)
            Destroy(gameObject);    // Destroy the Game Object this script component is attached to
        // We don't want more than one instance of a GameManager Game Object

        // When we load a new scene, normally all Game Objects of hierarchy will be destroyed
        // We want to use GameManager Game Object to keep track of score between scenes, so we want the GameManager
        // to persist between scenes
        DontDestroyOnLoad(gameObject);

        // In Unity, scripts are considered Game Object components
        // Angle brackets <> are used for taking a type as a parameter
        // GetComponent returns reference to any component of the type specified of the
        // Game Object it's called upon
        // So to access attributes of another script, we don't import that script, we do this
        // bullshit (i.e. call GetComponent<>)
        levelManager = GetComponent<LevelManager>();
        InitGame();
    }

    void InitGame()
    {
        levelManager.SetupScene();
    }

    public void GameOver()
    {
        enabled = false;    // Disable the GameManager script component 
    }
}
