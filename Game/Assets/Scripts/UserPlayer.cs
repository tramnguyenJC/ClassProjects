using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UserPlayer : MonoBehaviour {

    public float x;
    public float[] ys;
    private int curInd = 0;

    public static int numTroops = 0;

    // Containing the different types of trrops, each index matches to
    // a different type, sorted in increasing order of the troop type's
    // power.
    public List<GameObject> troops;

	// Use this for initialization
	void Start () {
		transform.position = new Vector3(x, ys[0], 0);
	}
	
	void Update()
    {
        if (Input.GetKeyDown("up"))
            MoveUp();
        else if (Input.GetKeyDown("down"))
            MoveDown();
        for (int i = 1; i <= troops.Count; ++i)
        {
            if (Input.GetKeyDown(i.ToString()))
            {
                DeployTroop(i-1);
            }
        }
    }

    protected void DeployTroop(int troopTypeInd)
    {
        Troop troop = Instantiate(troops[troopTypeInd], transform.position, Quaternion.identity).GetComponent<Troop>();
        troop.setId(numTroops);
        numTroops++;
    }

    public void MoveUp()
    {
        if (curInd == ys.Length - 1)
        {
            return;
        }
        curInd += 1;

        transform.position = new Vector3(x, ys[curInd], 0);
    }

    public void MoveDown()
    {
        if (curInd == 0)
        {
            return;
        }
        curInd -= 1;

        transform.position = new Vector3(x, ys[curInd], 0);
    }
}
