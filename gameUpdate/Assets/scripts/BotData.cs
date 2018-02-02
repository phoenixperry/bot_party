using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BotData :MonoBehaviour
{
    //this class deals with all bot data 
    public static string botName;
    public static ArrayList compass = new ArrayList();
    public static int btn;
    private static string[] sensors;
    public GameObject bot1;
    public GameObject bot2;
    public GameObject bot3; 
    public int integratedCompass; 
    public void updateData(string values)
    {
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
        routeData(); 
    }
    int btnDown = 0; 
    public void routeData() {
        
        if (botName == "botOne")
        {
            string val = compass[0] as string;
           
            int.TryParse(val, out integratedCompass);

            val = compass[1] as string;
            int xpos; 
            int.TryParse(val, out xpos);

            val = compass[2] as string;
            int ypos;
            int.TryParse(val, out ypos);

            val = compass[1] as string;
            int zpos;
            int.TryParse(val, out zpos);


            bot1.GetComponent<botBehavior>().rotateBot(xpos, ypos, zpos);
            if (btn == 1 && btnDown == 0)
            {
               
                btnDown = 1; 
                bot1.GetComponent<botBehavior>().triggerSound();
    
 

                var colors = bot1.GetComponent<botBehavior>().btn.colors;
                colors.normalColor = Color.red;
                bot1.GetComponent<botBehavior>().btn.colors = colors; 
                //Debug.Log(btnDown); 
            }
            else if(btn == 0 )
            {
                btnDown = 0;
                var colors = bot1.GetComponent<botBehavior>().btn.colors;
                colors.normalColor = Color.green;
                bot1.GetComponent<botBehavior>().btn.colors = colors;
            }
            
        }
        else if (botName == "botTwo")
        {

        }
        else {

        } 
         
    }

    
}
