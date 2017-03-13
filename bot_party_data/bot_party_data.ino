#include <Arduino.h>
const int numReadings = 10;
float average = 0;
int readIndex = 0;
int total = 0;
int previousAverage =0; 
int readings[numReadings];
float upperBounds = 20; 
float lowerBounds = 20; 
bool a2touched = false;
void setup() {
  Serial.begin(9600);
  for(int thisReading = 0; thisReading < numReadings; thisReading++)
    {
      readings[thisReading] = 0;
    }
}

void loop() {
 float value = touchRead(A2,A6);
//subtract the last reading
 total = total - readings[readIndex];
readings[readIndex]= value;
//add the reading to the total
total = total + readings[readIndex];
//advance to the next reading
readIndex = readIndex + 1;

//if we are at the end of the array
if(readIndex >= numReadings)
  readIndex = 0;
  
average = total/numReadings;

//this will give you 1,2 or 3 depending on which boxes are touched for box A2 
//it will not let you know if  A2 is picked up 
float val = map(value, 0, 1024, 0, 2); 
Serial.println(val);   


if(average > previousAverage - 50); 
{
  a2touched = true;
}
//Serial.println(a2touched);
//Serial.println(average);  
//delay(1); 
//Serial.println("A2 touched"); 

//Serial.println(average); 
//Serial.println("A2 touched"); 


//Serial.println(average); 

// float value2 = touchRead(A4,A6);
 
 //Serial.println(value2); 
// previousAverage = average; 
}
int touchRead(int pin1, int pin2)
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
    digitalWrite(pin1,LOW);
    sum = sum +high-low;  
  }

  return (int)((float)sum/4.0f);

}

bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

