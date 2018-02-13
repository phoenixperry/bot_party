using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Collections.Generic;
// capage 08/2/18

public class KeyboardReader : MonoBehaviour
{

	public GameObject botData;
	public GameObject touchData; 
	// Use this for initialization
	void Start()
	{
		// Get a list of serial port names in case we are not dealing with com3 .
		Debug.Log("Using Keyboard reader");

	}

	// Update is called once per frame
	void Update()
	{	
		touchData.GetComponent<TouchData>().clearAllTouches ();
			if (Input.GetKey(KeyCode.Q)) {
				Debug.Log("Key Q down: 1 and 2 are touching.");
				touchData.GetComponent<TouchData>().updateData("1 2");
				//Debug.Log(value);
			}
			if (Input.GetKey(KeyCode.W)) {
				Debug.Log("Key W down: 2 and 3 are touching.");
				touchData.GetComponent<TouchData>().updateData("2 3");
				//Debug.Log(value);
			}
			if (Input.GetKey(KeyCode.E)) {
				Debug.Log("Key E down: 1 and 3 are touching.");
				touchData.GetComponent<TouchData>().updateData("1 3");
				//Debug.Log(value);
			}

			if (Input.GetKeyDown(KeyCode.Alpha1)) {
				Debug.Log("Key 1 down: bot 1 button press");
				botData.GetComponent< BotData > ().updateData("botOne 0 0 0 0 1");
				//Debug.Log(value);
		} else if (Input.GetKeyUp(KeyCode.Alpha1)) {
			Debug.Log ("key 1 up");
				botData.GetComponent< BotData >().updateData("botOne 0 0 0 0 0");
			}

		if (Input.GetKeyDown(KeyCode.Alpha2)) {
			Debug.Log("Key 2 down: bot 2 button press");
			botData.GetComponent< BotData > ().updateData("botTwo 0 0 0 0 1");
			//Debug.Log(value);
		} else if (Input.GetKeyUp(KeyCode.Alpha2)) {
			Debug.Log ("key 2 up");
			botData.GetComponent< BotData >().updateData("botTwo 0 0 0 0 0");
		}

		if (Input.GetKeyDown(KeyCode.Alpha3)) {
			Debug.Log("Key 3 down: bot 3 button press");
			botData.GetComponent< BotData > ().updateData("botThree 0 0 0 0 1");
			//Debug.Log(value);
		} else if (Input.GetKeyUp(KeyCode.Alpha3)) {
			Debug.Log ("key 3 up");
			botData.GetComponent< BotData >().updateData("botThree 0 0 0 0 0");
		}

	}
}
