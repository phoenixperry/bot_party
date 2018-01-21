using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BotData :MonoBehaviour
{
    //this class deals with all bot data 
    public static string name;
    public static ArrayList compass = new ArrayList();
    public static int btn;
    private static string[] sensors;


    public void updateData(string values)
    {
        compass.Clear();
        sensors = values.Split(' '); //split the array at every space. we use a space to deliminate our values from Arduino 
        name = sensors[0]; //get which bot we're dealing with, which is saved in the 0 position 
                            // Debug.Log(name);
        compass.Add(sensors[1]);
        compass.Add(sensors[2]);
        compass.Add(sensors[3]);
        compass.Add(sensors[4]);
        int.TryParse(sensors[5], out btn);
        Debug.Log("Bot Parsed: " + name + " btn " + btn + "Compass vals" + compass[0] + " " + compass[1] + " " + compass[2] + " " + compass[3]);
    }


    
}
