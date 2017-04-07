#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#define HWSERIAL Serial3
int id = 00; 
//box pins 
const int box1 = A9; 
const int box2 = A8; 
const int box3 = A7; 

//calibration checks 
bool started = false; 

//++++++++++ FILP THIS TRUE TO SKIP OVER THE CALIBATION ROUTINE 
bool calibrated = true; 
bool skipBoxes = false; 

bool boxes2_3_calibrated=false; 
bool boxes1_3_calibrated=false; 
bool boxes1_2_calibrated=false; 

//data for averages 
int avBoxes1_2=21; 
int avBoxes1_3=21; 
int avBoxes2_3=21; 
int avBoxes1_2_3;

//inbetween box touching state bools
bool boxes1_2; 
bool boxes1_3; 
bool boxes2_3; 
bool allConnected; 


//compass values 
/* Assign a unique ID to this sensor at the same time */
//Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
//float comp_x;
//float comp_y;
//float comp_z;
//


//function prototypes 

//launches the calibration routine 
void calibrate(); 

//calibrates the boxes during the calibration routine 
int calibrateBoxes(int box_a, int box_b); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  HWSERIAL.begin(9600); 
  //vs doing the data in analog filters, we're cheating! Input_pullup is smoothing an analog pin
  pinMode(box1, INPUT_PULLUP);
  pinMode(box2, INPUT_PULLUP);
  pinMode(box3, INPUT_PULLUP);
  
  //calls the calibration routine 
  calibrate();  

     /* Initialise the compass */
//
//  mag.enableAutoRange(true);
//  if(!mag.begin())
//  {
//    /* There was a problem detecting the LSM303 ... check your connections */
//    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
//    while(1);
//  }
//
//   /* Initialise the sensor */
//  if(!accel.begin())

}

void loop() {

  //delimiter data
  
  Serial.print("00 "); 
  HWSERIAL.print("00 ");
  
  if(skipBoxes == false) 
  {   
    int ar = readTouches(box1, box2);
  
     ar = map(ar, 0, 1014, 0, 10); 
     boxes1_2 = inRange(ar, avBoxes1_2-5, avBoxes1_2+5); 
    
     Serial.print(boxes1_2);
     HWSERIAL.print(boxes1_2); 
     Serial.print(" ");
     HWSERIAL.print(" "); 
  //     
     ar = readTouches(box1, box3);
     ar = map(ar, 0, 1024, 0, 10); 
     boxes1_3 = inRange(ar, avBoxes1_3-5, avBoxes1_3+5); 
     
     Serial.print(boxes1_3); 
     HWSERIAL.print(boxes1_3);
     Serial.print(" "); 
     HWSERIAL.print(" "); 
     
     ar = readTouches(box2, box3);
     ar = map(ar, 0, 1024, 0, 10); 
     boxes2_3 = inRange(ar, avBoxes2_3-5, avBoxes2_3+5); 
    
     Serial.print(boxes2_3); 
     HWSERIAL.print(boxes2_3); 
     Serial.print(" ");
     HWSERIAL.print(" "); 
     
     if(boxes1_2 && boxes1_3 && boxes2_3)  
     {
      allConnected = true; 
     }else allConnected = false; 
  
     Serial.println(allConnected);
     HWSERIAL.println(allConnected);  
     delay(80); 
  }
//values for the compasses 
//
//    float heading = run_compass(comp_x,comp_y,comp_z);
//   
//    Serial.print(int(heading));
//    Serial.print(" ");
//     
//    Serial.print(int(comp_x));
//    Serial.print(" ");
//    
//    Serial.print(int(comp_y));
//    Serial.print(" ");
//
//    Serial.print(int(comp_z));
//    Serial.print(" ");

/*    
    heading = run_compass2(comp_x,comp_y, comp_z);
   
    Serial.print(int(heading));
    Serial.print(" ");
     
    Serial.print(int(comp_x));
    Serial.print(" ");
    
    Serial.print(int(comp_y));
    Serial.print(" ");

    Serial.print(int(comp_z));
    Serial.print(" ");
*/

    // values for the accelerometer

/* Get a new sensor event */
/*
    sensors_event_t event;
    accel.getEvent(&event);

    acc_x = event.acceleration.x;
    acc_y = event.acceleration.y;
    acc_z = event.acceleration.z;   

    Serial.print(int(acc_x));
    Serial.print(" ");
     
    Serial.print(int(acc_y));
    Serial.print(" ");
    
    Serial.print(int(acc_z));
    Serial.println(" ");
    */

//    float ac = run_accel(acc_x, acc_y, acc_z);
//    Serial.print(int(ac));
//    Serial.print(" ");
//    Serial.print(int(acc_x));
//    Serial.print(" ");
//    Serial.print(int(acc_y));
//    Serial.print(" ");
//    Serial.print(int(acc_z));
//    Serial.print(" ");


    

//  bool box1_touched = isolatedTouches(box1);  
//  bool box2_touched = isolatedTouches(box2);
//  bool box3_touched = isolatedTouches(box3);  
////  Serial.print(box1_touched); 
////  Serial.print(" "); 
////  Serial.print(box2_touched);
////  Serial.print(" ");  
////  Serial.println(box3_touched); 

}

bool isolatedTouches(int pin){

   analogWrite(pin, HIGH);
   int touch = analogRead(pin);
   touch = map(touch, 0,1024, 0, 20); 
   Serial.println(touch);  
   if(touch < 8) 
   return true; 
   else 
   return false; 
   digitalWrite(pin, LOW);
} 

int readTouches(int pin1, int pin2)
{
 int sum=0;

 for(int i=0; i < 10; i++)
 {
   pinMode(pin1, OUTPUT);
   digitalWrite(pin1,HIGH);
   //delayMicroseconds(10);
   int high = analogRead(pin2);

   digitalWrite(pin1,LOW);
   //delayMicroseconds(10);
   int low = analogRead(pin2);


   pinMode(pin1, INPUT);
//   digitalWrite(pin1,LOW);

   sum = sum +high-low;
 }
 //Serial.println("!"); 
 return (int)((float)sum/4.0f);
}

void calibrate(){
   while(!calibrated) {
    // put your main code here, to run repeatedly:
    String incoming = Serial.readStringUntil('\n');
     
    if (started==false)

    { 
      Serial.println("touch boxes 1 & 2 then type ! in the above text box & enter"); 
    }
    
    if(incoming.length() > 0);{
      //note incoming includes a return character and new line (two bytes)  
      
      if(incoming == "!" && boxes1_2_calibrated == false) 
       {  
        started = true; 
        avBoxes1_2 = calibrateBoxes(box1, box2); 
        Serial.println("Done calibrating boxes 1&2"); 
        Serial.print("Their average is saved "); 
        Serial.println(avBoxes1_2); 
        Serial.println("Now touch box1 and box3 and type @ & enter to proceed"); 
        boxes1_2_calibrated = true; 
       } 
    }
    ///now calibrating boxes 1&3 
    if(incoming == "@" &&boxes1_2_calibrated)
    {
        avBoxes1_3 = calibrateBoxes(box1, box3); 
        Serial.println("Done calibrating boxes 1&3"); 
        Serial.print("Their average is saved "); 
        Serial.println(avBoxes1_3); 
        Serial.println("Now touch box2 and box3 and type # & enter to proceed"); 
        boxes1_3_calibrated = true; 
    }
     ///now calibrating boxes 2&3
    if(incoming == "#" &&boxes1_3_calibrated)
    {
        avBoxes2_3 = calibrateBoxes(box2, box3); 
        Serial.println("Done calibrating boxes 2&3"); 
        Serial.print("Their average is saved "); 
        Serial.println(avBoxes2_3); 
        Serial.println("That's it! We're about to start up data sending!"); 
        boxes2_3_calibrated = true; 
        calibrated = true; 
        delay(1500); 
    } 
  }
} 

int calibrateBoxes(int box_a, int box_b){
        Serial.println("You've got 2 seconds to touch boxes! Starting up");
        delay(2000); 
        double startTime = millis();
        double endTime = startTime + 5000; 
    
   
        int total = 0; 
        int samples = 0; 
    
          while(startTime < endTime)
          {
            Serial.println("reading for 5 seconds"); 
            int theseBoxes = readTouches(box_a, box_b);
            theseBoxes = map(theseBoxes, 0, 1024, 0, 10);
          
             
            Serial.println(theseBoxes); 
            startTime = millis();

            //safe guarding against bad touches. 
             if(theseBoxes > 2) 
             {
              total = theseBoxes + total; 
              samples = samples+1;
             }
            
            delay(100); 
          }
          
    return total/samples;  
} 

bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

    
//float run_compass(float &compass_x, float &compass_y, float &compass_z) {
//  //compass code
//  /* Get a new sensor event */
//  sensors_event_t event;
//  mag.getEvent(&event);
//
//  float Pi = 3.14159;
//
//  compass_x = event.magnetic.x;
//  compass_y = event.magnetic.y;
//  compass_z = event.magnetic.z;
//
//  // Calculate the angle of the vector y,x
//  float heading = (atan2(compass_y,compass_x) * 180) / Pi;
//
//  // Normalize to 0-360
//  if (heading < 0)
//  {
//    heading = 360 + heading;
//  }
//  //Serial.print("Compass Heading: ");
//  return heading;
//}
//

