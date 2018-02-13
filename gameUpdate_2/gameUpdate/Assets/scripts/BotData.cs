using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BotData : MonoBehaviour
{
    //this class deals with all bot data 
    public static string botName;
    public static ArrayList compass = new ArrayList();
    public static int btn;
    private static string[] sensors;
    public GameObject bot1;
    public GameObject bot2;
    public GameObject bot3;
	public int[] btnsDown = {0, 0, 0};
	public GameObject[] bots = {null, null, null};

    public int integratedCompass;
	void Start() {
		bots [0] = bot1; bots [1] = bot2; bots [2] = bot3;
	}
	void Update() {
		transform.Find("TouchState").GetComponent<TextMesh> ().text = getTouchState().ToString();
	}
	public int getTouchState() {
		// 0: No touches
		// 1: Just 1 and 2
		// 2: Just 2 and 3
		// 3: Just 1 and 3 
		// 4: All together.
		int sum = 0;
		for (int i = 0; i < bots.Length; i++) {
			// Why does c sharp not have a built-in for summing an array jesus
			for (int j = 0; j < bots [i].GetComponent<botBehavior> ().touching.Length; j++) {
				if (bots [i].GetComponent<botBehavior> ().touching [j] == 1) {
					sum += 1;
				}
			}
			if (sum == 2) { 
				return 4; // if one is touching 2 there's a circle
			}
			if (sum != 0) {
				break; // Means it's either 1, 2 or 3.
			}
		}
		if (sum == 0) {
			return 0; // Noone's touching anyone -> 0
		}
		if (bots [0].GetComponent<botBehavior> ().touching [1] == 1) {
			return 1;
		}
		if (bots [0].GetComponent<botBehavior> ().touching [2] == 1) {
			return 3;
		}
		if (bots [1].GetComponent<botBehavior> ().touching[2] == 1) {
			return 2;
		}
		return -1;
	}

    public void updateData(string values)
    {
		bots [0] = bot1;
		bots [1] = bot2;
		bots [2] = bot3;
		compass.Clear();
        sensors = values.Split(' '); //split the array at every space. we use a space to deliminate our values from Arduino 
        botName = sensors[0]; //get which bot we're dealing with, which is saved in the 0 position 
                            // Debug.Log(name);
        compass.Add(sensors[1]);
        compass.Add(sensors[2]);
        compass.Add(sensors[3]);
        compass.Add(sensors[4]);
        int.TryParse(sensors[5], out btn);
        //Debug.Log("Bot Parsed: " + botName + " btn " + btn + "Compass vals" + compass[0] + " " + compass[1] + " " + compass[2] + " " + compass[3]);
        //Debug.Log(botName+ botName.Length);
		int bot_id = 0;
		if (botName == "botOne") {
			bot_id = 1;
		} else if (botName == "botTwo") {
			bot_id = 2;
		} else if (botName == "botThree") {
			bot_id = 3;
		}
		updateBot (bot_id, sensors);
        //routeData(); 
    }

	public void updateBot(int bot, string[] sensors){
		GameObject bot_object = bots [bot-1];
		string val = sensors[1] as string;

		int.TryParse(val, out integratedCompass);

		val = sensors[2] as string;
		int xpos;
		int.TryParse(val, out xpos);

		val = sensors[3] as string;
		int ypos;
		int.TryParse(val, out ypos);

		val = sensors[4] as string;
		int zpos;
		int.TryParse(val, out zpos);

		val = sensors [5] as string;
		int btn;
		int.TryParse (val, out btn);


		bot_object.GetComponent<botBehavior>().rotateBot(xpos, ypos, zpos);
		if (btn == 1 && btnsDown[bot-1] == 0)
		{
			btnsDown[bot-1] = 1;
			bot_object.GetComponent<botBehavior>().triggerSound();



			var colors = bot_object.GetComponent<botBehavior>().btn.colors;
			colors.normalColor = Color.green;
			bot_object.GetComponent<botBehavior>().btn.colors = colors;
			//Debug.Log(btnDown); 
		}
		else if (btn == 0)
		{
			btnsDown[bot-1] = 0;
			var colors = bot_object.GetComponent<botBehavior>().btn.colors;
			colors.normalColor = Color.red;
			bot_object.GetComponent<botBehavior>().btn.colors = colors;
		}
	}
}
