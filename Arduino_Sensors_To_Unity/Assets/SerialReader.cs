using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Collections.Generic;


public class SerialReader : MonoBehaviour
{

    SerialPort stream = new SerialPort("COM3", 9600);
    bool firstTime = true;
    public GameObject botData;
    public GameObject touchData; 
    // Use this for initialization
    void Start()
    {
        stream.Open();
    }

    // Update is called once per frame
    void Update()
    {
        stream.ReadTimeout = 40; // this is a safety catch in case the port hangs
        try
        {
            string value = stream.ReadLine();
            string[] sensors = value.Split(' ');
            //foreach (string s in sensors)
            //{ 
            //   if(s != "") 
            //        Debug.Log(s);
                 
            //}
       
            //if we have 2 values, we have a touch state 
            if (sensors.Length == 2)
            {
                touchData.GetComponent<BotData>().updateData(value);
            }
            else if (sensors.Length == 6) {
                botData.GetComponent< BotData > ().updateData(value);
          
           }

            stream.BaseStream.Flush();
        }
        catch (System.Exception e) {
            //Debug.Log("your serial port shit the bed. try unplugging your arduino and reloading your code on it"); 
        }
 
   }
}
