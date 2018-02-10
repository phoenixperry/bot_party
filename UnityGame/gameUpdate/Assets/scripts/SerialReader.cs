using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Collections.Generic;


public class SerialReader : MonoBehaviour
{
    
    SerialPort stream = new SerialPort("COM4", 9600); //this is for the port you're on = it has to match what arduino is plugged into       

    public GameObject botData;
    public GameObject touchData; 
    // Use this for initialization
    void Start()
    {
        // Get a list of serial port names in case we are not dealing with com3 .
        string[] ports = SerialPort.GetPortNames();

        Debug.Log("The following serial ports were found:");

        // Display each port name to the console.
        foreach (string port in ports)
        {
            Debug.Log(port);
        }

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
            Debug.Log(value); 
            //foreach (string s in sensors)
            //{
            //    if (s != "")
            //        Debug.Log(s);

            //}

            //if we have 2 values, we have a touch state 
            //Debug.Log(sensors.Length);
        if (sensors.Length > 1 && sensors.Length < 4)
            {
                touchData.GetComponent<TouchData>().updateData(value);
                //Debug.Log(value);
            }
            else if (sensors.Length == 6) {
                botData.GetComponent< BotData > ().updateData(value);
                //Debug.Log(value);

            }

            stream.BaseStream.Flush();
        }
        catch (System.Exception e) {
            //Debug.Log("your serial port shit the bed. try unplugging your arduino and reloading your code on it"); 
        }
 
   }
}
