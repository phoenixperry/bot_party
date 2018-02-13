using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TouchTarget : MonoBehaviour {

	// Use this for initialization
	int target = 0;
	int score = 0;
	void Start () {
		target = newTarget ();
	}

	int newTarget() {
		int n = target;
		while (n == target) {
			n = Random.Range (1, 5);
		}
		return n;
	}
	
	// Update is called once per frame
	void Update () {
		GetComponent<TextMesh> ().text = "Target: " + target+"\n Score: "+score;
		if (transform.GetComponentInParent<BotData> ().getTouchState () == target) {
			target = newTarget ();
			score += 1;
			Debug.Log ("Score!");
		}

	}
}
