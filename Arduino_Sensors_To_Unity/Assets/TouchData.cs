using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TouchData : MonoBehaviour {

    public class Touches
    {
        //    //this class handles all of the touches between boxes 

            public static string touchingBoxes; //what boxes are touching 
            public static int touch = 0; //touch state 
        

        public void updateData(string value)
        {
            string[] sensors = value.Split(' '); //split the stinrg we got from arduino using a space as the delimiter of the string 
                touchingBoxes = sensors[0]; //the first value indicate which boxes are are testing for being connected 
            int.TryParse(sensors[1], out touch); //get the string value of the touch state and convert it to an int for sanity
            //Debug.Log("Touch Parsed: " + touchingBoxes + " touch state " +touch);
        }
    }

}
