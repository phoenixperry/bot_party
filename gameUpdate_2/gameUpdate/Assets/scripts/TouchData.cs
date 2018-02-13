using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TouchData : MonoBehaviour {

        //    //this class handles all of the touches between boxes 

            public static int touchingBoxes; //what boxes are touching 
            public static int touch = 0; //touch state 
        
		public GameObject bot1;
		public GameObject bot2;
		public GameObject bot3;
	public void clearAllTouches() {
		bot1.GetComponent<botBehavior> ().clearTouches ();
		bot2.GetComponent<botBehavior> ().clearTouches ();
		bot3.GetComponent<botBehavior> ().clearTouches ();
	}
        public void updateData(string value)
        {
		GameObject[] bots = { bot1, bot2, bot3 };
            string[] sensors = value.Split(' '); //split the stinrg we got from arduino using a space as the delimiter of the string 
		    int.TryParse(sensors[0], out touchingBoxes); //the first value indicate which boxes are are testing for being connected 
            int.TryParse(sensors[1], out touch); //get the string value of the touch state and convert it to an int for sanity
            //Debug.Log("Touch Parsed: " + touchingBoxes + " touch state " +touch);
		Debug.Log(touchingBoxes+" is touching "+touch);
		bots [touchingBoxes - 1].GetComponent<botBehavior> ().touching [touch - 1] = 1;
		bots [touch - 1].GetComponent<botBehavior> ().touching [touchingBoxes - 1] = 1;
        }
    

}
