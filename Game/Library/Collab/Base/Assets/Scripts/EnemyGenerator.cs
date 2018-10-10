using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyGenerator : MonoBehaviour {
	// The x coordinate of locations in which Enemy can be 
	// generated.
	public float x;
	// Array of all possible y's positions in which the Enemy
	// can be generated.
    public float[] ys;

    // Current y-index in the ys array of possible y's positions.
    private int curInd = 0;

    // Containing the different types of trrops, each index matches to
    // a different type, sorted in increasing order of the troop type's
    // power.
    public List<GameObject> troops;

    // Pre-specified range for the minimum and maximum number of seconds that
    // have passed before a new enemy can be randomly generated.
    public float minSecondsPassedBeforeNextEnemy;
    public float maxSecondsPassedBeforeNextEnemy;

    // The number of seconds that has passed before a new enemy can be randomly
    // generated, clamped by the range specified.
    private float secondsPassedBeforeNextEnemy;


	// Use this for initialization
	void Start () {
		transform.position = new Vector3(x, ys[0], 0);
		// Randomly generated secondsPassedBeforeNextEnemy within range.
		RandomlyDeployTroop();
		secondsPassedBeforeNextEnemy =  Random.Range(
    		minSecondsPassedBeforeNextEnemy, maxSecondsPassedBeforeNextEnemy);
	}
	
	// Enemy generating is completely random for now.
	void Update()
    {
    	secondsPassedBeforeNextEnemy -= Time.deltaTime;
    	if (secondsPassedBeforeNextEnemy <= 0) {
    		// Time reached, generate a new enemy randomly.
    		RandomlyDeployTroop();
    		// Reset secondsPassedBeforeNextEnemy to a new value.
    		secondsPassedBeforeNextEnemy =  Random.Range(
    			minSecondsPassedBeforeNextEnemy,
    			maxSecondsPassedBeforeNextEnemy);
    	}
    }

    protected void RandomlyDeployTroop() {
    	curInd = Random.Range(0, ys.Length);
    	int troopTypeIdx = Random.Range(0, troops.Count);
    	DeployTroop(troopTypeIdx);
    }

    protected void DeployTroop(int troopInd)
    {
   		transform.position = new Vector3(x, ys[curInd], 0);
        Instantiate(troops[troopInd], transform.position, Quaternion.identity).GetComponent<Troop>();
    }

}
