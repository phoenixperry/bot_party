 
#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
#include <Arduino.h>
#define box1 A0  
#define box2 A1 
#define box3 A2

//mpr121 
// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4


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
void setup() {
  Serial.begin(9600);
  for(int thisReading = 0; thisReading < numReadings; thisReading++)
    {
      readings[thisReading] = 0;
    }
      if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);
   // this is the touch threshold - setting it low makes it more like a proximity trigger
  // default value is 40 for touch
  MPR121.setTouchThreshold(7);
  
  // this is the release threshold - must ALWAYS be smaller than the touch threshold
  // default value is 20 for touch
  MPR121.setReleaseThreshold(4);  


    // slow down some of the MPR121 baseline filtering to avoid 
  // filtering out slow hand movements
  MPR121.setRegister(MPR121_NHDF, 0x01); //noise half delta (falling)
  MPR121.setRegister(MPR121_FDLF, 0x3F); //filter delay limit (falling)   
  
}

void loop() {
readTouchInputs(); 
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

int pinCheck = analogRead(A0); 
Serial.println(pinCheck); 

float box1_3 = touchRead1(box1,box3); 

float box2_3 = touchRead1(box2,box3);
int val = map(box1_3, 0, 1024, 0, 5); 

//printing the connected states out to Strings for Max
if(val == 0) Serial.println("no boxes connected"); 
//
bool range = inRange(val, 2,3);
if(range)Serial.println("box 1 and box 2 connected");

range = inRange(val, 10,11);
if(range) 
{
  Serial.println("box 1 and box 3 connected");
    boxes_1_3_connected = true; 
}else boxes_1_3_connected = false; 


//
val = map(box2_3, 0, 1024, 0, 4);
//Serial.println(val);  
// 
range = inRange(val, 8,9);
if(range) 
  {
    Serial.println("box 2 and 3 connected");  
    boxes_2_3_connected = true;  
  }else boxes_2_3_connected = false; 

if(boxes_2_3_connected && boxes_1_3_connected) Serial.println("all 3 connected"); 
 
 
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
  return ((minimum <= val) && (val <= maximum));
}

int digitalSmooth(int rawIn, int *sensSmoothArray){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  int j, k, temp, top, bottom;
  long total;
  static int i;
 // static int raw[filterSamples];
  static int sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

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

}
void readTouchInputs(){
    
  MPR121.updateAll();

  // only make an action if we have one or fewer pins touched
  // ignore multiple touches

  for (int i=1; i < 12; i++){  // Check which electrodes were pressed
    if(MPR121.isNewTouch(i)){
    
        //pin i was just touched
        Serial.print("pin ");
        Serial.print(i);
        Serial.println(" was just touched");  
    }else{
      if(MPR121.isNewRelease(i)){
        Serial.print("pin ");
        Serial.print(i);
        Serial.println(" is no longer being touched");
        digitalWrite(LED_BUILTIN, LOW);
     } 
    }
  }
}
