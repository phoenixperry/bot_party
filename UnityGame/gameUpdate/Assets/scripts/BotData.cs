
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

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

    public Button btn1;
    public Button btn2;
    public Button btn3; 

    public int integratedCompass;
    int btn1Down = 0; //saves btn down state 
    int btn2Down = 0;
    int btn3Down = 0;


    public void Start() {
        bot1 = Instantiate(bot1, new Vector3(-3.0f, 1.0f, 0.0f), Quaternion.identity) as GameObject;
        bot2 = Instantiate(bot2, new Vector3(0.0f, 1.0f, 0.0f), Quaternion.identity) as GameObject;
        bot3 = Instantiate(bot3, new Vector3(3.0f, 1.0f, 0.0f), Quaternion.identity) as GameObject;
        bot1.GetComponent<botBehavior>().setBtn(btn1);
        bot2.GetComponent<botBehavior>().setBtn(btn2);
        bot3.GetComponent<botBehavior>().setBtn(btn3);
    }
    
    public void updateData(string values)

    {
        compass.Clear();
        sensors = values.Split(' '); //split the array at every space. we use a space to deliminate our values from Arduino 
        botName = sensors[0]; //get which bot we're dealing with, which is saved in the 0 position 
        // Debug.Log(name);
        compass.Add(sensors[1]); //integrated compass 
        compass.Add(sensors[2]); //x 
        compass.Add(sensors[3]); //y
        compass.Add(sensors[4]); //z  
        int.TryParse(sensors[5], out btn); //btn

        //Debug.Log("Bot Parsed: " + botName + " btn " + btn + "Compass vals" + compass[0] + " " + compass[1] + " " + compass[2] + " " + compass[3]);
        //Debug.Log(botName+ botName.Length); 
        routeData();
    }
    public void routeData()
    {
        if (botName == "botOne")
        {
            //route teh compass values 
            string val = compass[0] as string;
            int.TryParse(val, out integratedCompass);
            //eventually, the compass data should be passed to the functions that need it here 

            //route the accelerometer values 
            val = compass[1] as string;
            int xpos;
            int.TryParse(val, out xpos);
            val = compass[2] as string;
            int ypos;
            int.TryParse(val, out ypos);
            val = compass[3] as string;
            int zpos;
            int.TryParse(val, out zpos);
            //send the accelerometer vals to the bot using them  
            bot1.GetComponent<botBehavior>().rotateBot(xpos, ypos, zpos); // move the bot by the x, y, z positions 
            //if the btn is down  & and it was not down in the last frame  
            if (btn == 1 && btn1Down == 0)
            {
                Debug.Log("btn 1 fired");
                //flip on the bool that checks if it is down on so it does not trigger repeatedly. 
                btn1Down = 1;
                bot1.GetComponent<botBehavior>().triggerSound(); //trigger the sound 
                var colors = btn1.colors;
                colors.normalColor = Color.red;
                btn1.colors = colors;
            }
            else if (btn == 0)
            {
                btn1Down = 0; //reset the btn flag so the button can fire again 
                              //create a color then assign it through to the btn to show it's off now 
                var colors = btn1.colors;
                colors.normalColor = Color.green;
                btn1.colors = colors;
            }

        } else if (botName == "botTwo")
        {
            //route teh compass values 
            string val = compass[0] as string;
            int.TryParse(val, out integratedCompass);
            //eventually, the compass data should be passed to the functions that need it here 
            //route the accelerometer values 
            val = compass[1] as string;
            int xpos;
            int.TryParse(val, out xpos);
            val = compass[2] as string;
            int ypos;
            int.TryParse(val, out ypos);
            val = compass[3] as string;
            int zpos;
            int.TryParse(val, out zpos);
            //send the accelerometer vals to the bot using them  
            bot2.GetComponent<botBehavior>().rotateBot(xpos, ypos, zpos); // move the bot by the x, y, z positions 

            if (btn == 1 && btn2Down == 0)
            {
                Debug.Log("btn 2 fired");
                //flip on the bool that checks if it is down on so it does not trigger repeatedly. 
                btn2Down = 1;
                bot2.GetComponent<botBehavior>().triggerSound(); //trigger the sound 
                var colors = btn2.colors;
                colors.normalColor = Color.red;
                btn2.colors = colors;
            } else if (btn == 0)
            {
                btn2Down = 0; //reset the btn flag so the button can fire again
                              //create a color then assign it through to the btn to show it's off now 
                var colors = btn2.colors;
                colors.normalColor = Color.green;
                btn2.colors = colors;
            }
        } else if (botName == "botThree")
        {
            //route teh compass values 
            string val = compass[0] as string;
            int.TryParse(val, out integratedCompass);
            //eventually, the compass data should be passed to the functions that need it here 

            //route the accelerometer values 
            val = compass[1] as string;
            int xpos;
            int.TryParse(val, out xpos);
            val = compass[2] as string;
            int ypos;
            int.TryParse(val, out ypos);
            val = compass[3] as string;
            int zpos;
            int.TryParse(val, out zpos);
            //send the accelerometer vals to the bot using them  
            bot3.GetComponent<botBehavior>().rotateBot(xpos, ypos, zpos); // move the bot by the x, y, z positions 

            if (btn == 1 && btn3Down == 0)
            {
                Debug.Log("btn 3 fired");
                //flip on the bool that checks if it is down on so it does not trigger repeatedly. 
                btn3Down = 1;
                bot3.GetComponent<botBehavior>().triggerSound(); //trigger the sound 
                var colors = btn3.colors;
                colors.normalColor = Color.red;
                btn3.colors = colors;
            } else if (btn == 0)
            {
                btn3Down = 0; //reset the btn flag so the button can fire again 
                              //create a color then assign it through to the btn to show it's off now 
                var colors = btn3.colors;
                colors.normalColor = Color.green;
                btn3.colors = colors;
            }
      }
    
    }
 }
