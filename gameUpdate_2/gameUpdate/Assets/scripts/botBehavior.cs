using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; 
public class botBehavior : MonoBehaviour {
	public int bot_id;
	public int[] touching = {0, 0, 0};
    public Button btn; 
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		//Debug.Log ("Bot " + bot_id + " is touching: " + touching[0] + ", "+touching[1]+","+touching[2]);
		string str = "Bot "+bot_id+":";
		if (touching [0] == 1) {
			str += "1, ";
		}
		if (touching [1] == 1) {
			str += "2, ";
		}
		if (touching [2] == 1) {
			str += "3, ";
		}
		transform.GetChild(0).GetComponent<TextMesh>().text = str;
	}

	public void clearTouches(){
		touching [0] = 0; touching [1] = 0; touching [2] = 0;
	}

    public void rotateBot(int xpos, int ypos, int zpos) {

        //TODO: make this a reasonable animation in the future 
        Vector3 angles = new Vector3((float)xpos, (float)ypos, (float)zpos);
        transform.Rotate(angles);     
    }

    public void triggerSound() {
        btn.onClick.Invoke();
    }

}
