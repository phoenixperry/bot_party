 
#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
#include <Arduino.h>
#define box1 A1  
#define box2 A8 
#define box3 A9
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

void setup() {
  Serial.begin(9600);
  for(int thisReading = 0; thisReading < numReadings; thisReading++)
    {
      readings[thisReading] = 0;
    }
}

void loop() {

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

float box1_3 = touchRead1(box1,box3); 

float box2_3 = touchRead1(box2,box3);

//Serial.print(value);   
//Serial.print(",");  
//Serial.println(value2);
  
int val = map(box2_3, 0, 1024, 0, 5); 

int smoothData0 = digitalSmooth(val, sensSmoothArray0); 
Serial.println(val);   

//printing the connected states out to Strings for Max
//if(val <= 4) Serial.println("no boxes connected"); 
//bool range = inRange(val, 5,7);
//if(range) Serial.println("box 1 and box 2 connected");
//if(val >= 11) Serial.println("box 2 and 3 connected");  
//if(val == 0) Serial.print("box 1 and box 3 connected"); 
//range = inRange(val, 8,10);
//if(range) Serial.println("all 3 connected"); 
 
//Touch data for pins 

  int touch0 = touchRead(box1); 
  
  int touchSmooth0 = digitalSmooth(touch0, touch0SmoothArray0); 
  //Serial.println(touchSmooth0); 
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
  return total / k;    // divide by number of samples
}
//returns string with 1 for touched and 0 for not touched for each pin passed in
void getTouches (int pin0, int pin1, int pin2){
  int touch0 = touchRead(pin0); 
  if(touch0 > 3000) touch0 = 1; 
  delay(10); 
  int touch1 = touchRead(pin1); 
  if(touch1 > 3000) touch1 = 1; 
  delay(10);
  int touch2 = touchRead(pin2); 
  if(touch2 > 3000) touch2 = 1; 
  Serial.println(touch1); 
  touchValues = String(touch0, touch1); 
}

