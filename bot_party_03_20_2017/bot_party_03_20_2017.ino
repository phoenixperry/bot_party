#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
#include <Arduino.h>
#define box1 A9
#define box2 A8
#define box3 A7

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);


const int numReadings = 10;
float average = 0;
int readIndex = 0;
int total = 0;
int readings[numReadings];

int touchReading = 0;
int sensSmoothArray1 [filterSamples];   // array for holding raw sensor values for sensor1
int sensSmoothArray2 [filterSamples];
int sensSmoothArray0 [filterSamples];

int touch0SmoothArray0 [filterSamples];

String touchValues;
bool boxes_1_3_connected =false;
bool boxes_2_3_connected = false;
bool boxes_1_2_connected = false;
bool all_boxes_connected = false;
bool no_boxes_connected = false;

void setup() {
 Serial.begin(9600);

 for(int thisReading = 0; thisReading < numReadings; thisReading++)
   {
     readings[thisReading] = 0;
   }

   /* Initialise the compass */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void loop() {
Serial.println("!");
float box1_3 = touchRead1(box1,box3);

float box2_3 = touchRead1(box2,box3);

int val = map(box1_3, 0, 1024, 0, 5);
val = digitalSmooth(val, sensSmoothArray0);

//printing the connected states out to Strings for Max
//if(val <= 2) //Serial.println("no boxes connected");
//Serial.println(val);
bool range = inRange(val, 2,4);
//Serial.println(range);
if(range)
{
  //Serial.println("box 1 and box 2 connected");
  boxes_1_2_connected = true;
}else boxes_1_2_connected = false;


range = inRange(val, 7,8);
if(range)
{
//Serial.println("box 1 and box 3 connected");
  boxes_1_3_connected = true;
}else boxes_1_3_connected = false;

val = map(box2_3, 0, 1024, 0, 5);

val = digitalSmooth(val, sensSmoothArray1);

range = inRange(val, 7,11);
Serial.println(val);
if(range)
 {
   //Serial.println("box 2 and 3 connected");
   boxes_2_3_connected = true;
 }else boxes_2_3_connected = false;

if(boxes_2_3_connected && boxes_1_3_connected)
{
  //Serial.println("all 3 connected+++++++++");
  all_boxes_connected = true;
}else all_boxes_connected = false;

/////////////Prints the touch states
Serial.print(boxes_2_3_connected);
Serial.print(" ");
Serial.print(boxes_1_3_connected);
Serial.print(" ");
Serial.print(boxes_1_2_connected);
Serial.print(" ");
Serial.print(all_boxes_connected);
Serial.print(" ");
//////////////

//float heading = run_compass();
int heading = 0;
Serial.print(heading);

Serial.print(heading);
Serial.print(" ");

Serial.print(heading);
Serial.print(" ");

}

float run_compass(){
//compass code
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  //Serial.print("Compass Heading: ");
  return heading;
}
int touchRead1(int pin1, int pin2)
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

 return (int)((float)sum/4.0f);

}

bool inRange(int val, int minimum, int maximum)
{

 done = 0;                // flag to know when we're done sorting
 while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
   done = 1;
   for (j = 0; j < (filterSamples - 1); j++){
     if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
       temp = sorted[j + 1];
       sorted [j+1] =  sorted[j] ;
       sorted [j] = temp;
       done = 0;
     }
   }
 }

/*
 for (j = 0; j < (filterSamples); j++){    // print the array to debug
   Serial.print(sorted[j]);
   Serial.print("   ");
 }
 Serial.println();
*/

 // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
 bottom = max(((filterSamples * 15)  / 100), 1);
 top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
 k = 0;
 total = 0;
 for ( j = bottom; j< top; j++){
   total += sorted[j];  // total remaining indices
   k++;
   // Serial.print(sorted[j]);
   // Serial.print("   ");
 }

//  Serial.println();
//  Serial.print("average = ");
//  Serial.println(total/k);
//  return total / k;    // divide by number of samples

}= maximum));
}



//void runningAverage(){
//this code will keep a running averege - currently unused
////subtract the last reading
// total = total - readings[readIndex];
//readings[readIndex]= value;
////add the reading to the total
//total = total + readings[readIndex];
////advance to the next reading
//readIndex = readIndex + 1;
//
////if we are at the end of the array
//if(readIndex >= numReadings)
//  readIndex = 0;

//average = total/numReadings;

//this maping and smoothing function gives me values for if the boxes are
//innerconnected in various ways

//}

void calibrate(){
      Serial.println("calibrating");
       String s = Serial.readStringUntil('\r\n');
       if(s == "!"){
          Serial.println("! fired");
        }

  }
