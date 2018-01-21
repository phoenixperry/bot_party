/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
int lf = 10;    // Linefeed in ASCII
String myString = null;

int[] lm303_1= new int[6]; 
int[] lm303_2= new int[6];
int[] lm303_3= new int[6]; 
int btn1, btn2, btn3; 
int touch1, touch2, touch3, touch4; 

void setup() 
{
  size(200, 200);

  // List all the available serial ports
  printArray(Serial.list());
 
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
  myPort.clear(); // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  
}

void draw() {
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
     //println(myString);
      String myTemp = myString;
      String[] prefix = splitTokens(myTemp, " ");
    println(prefix.length); 
        if(prefix.length == 4) {
          println("touch coming in "); 
           touch1 = int(prefix[0]);
           println(prefix[0]); 
           touch1 = int(prefix[1]);
           println(prefix[1]); 
           touch1 = int(prefix[2]);
           println(prefix[2]); 
           touch1 = int(prefix[3]);
           println(prefix[3]); 
        } 
        
        if(prefix.length == 11){ 
         int deviceID = int(prefix[0]); 
         
         ///compare for touches vs accel 
         if(deviceID == 03) 
         {
           lm303_3[0] = int(prefix[1]);
           lm303_3[1] = int(prefix[2]);
           lm303_3[2] = int(prefix[3]);
           lm303_3[3] = int(prefix[4]);
           lm303_3[4] = int(prefix[5]);
           lm303_3[5] = int(prefix[6]);
           //lm303_3[7] = int(prefix[7]);          
           //lm303_3[8] = int(prefix[8]);
           
           btn3 = int(prefix[9]); 
         }
         if(deviceID == 02) 
         {
           lm303_2[0] = int(prefix[1]);
           lm303_2[1] = int(prefix[2]);
           lm303_2[2] = int(prefix[3]);
           lm303_2[3] = int(prefix[4]);
           lm303_2[4] = int(prefix[5]);
           lm303_2[5] = int(prefix[6]);
           //lm303_2[7] = int(prefix[7]);          
           //lm303_2[8] = int(prefix[8]);
           btn2 = int(prefix[9]); 
         }
         if(deviceID == 01) 
         {
           lm303_1[0] = int(prefix[1]);
           lm303_1[1] = int(prefix[2]);
           lm303_1[2] = int(prefix[3]);
           lm303_1[3] = int(prefix[4]);
           lm303_1[4] = int(prefix[5]);
           lm303_1[5] = int(prefix[6]);
           lm303_1[7] = int(prefix[7]);          
           lm303_1[8] = int(prefix[8]);
           btn1 = int(prefix[9]); 
           //the last value freaks out if cast to an int
         }
        }
    }
  }

}