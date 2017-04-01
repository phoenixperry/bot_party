#define HWSERIAL Serial3
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
int btnPin = 12; 
String botID = "01:"; 
int ledPin = 10; 
int pulse = 0; 
int pulseSpeed = 1; 
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(1);

void setup(void) 
{
  
  Serial.begin(9600);
  HWSERIAL.begin(9600); 
  while(!Serial); 
    Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  pinMode(btnPin, INPUT_PULLUP); 
}

void loop(void) 
{
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
  HWSERIAL.print(botID);
  HWSERIAL.print(heading);
  HWSERIAL.print(" "); 
  int btn = digitalRead(btnPin); 
   
  if(btn == 0) 
  {
    HWSERIAL.println("1"); 
    analogWrite(ledPin,255);
  }else
  {
    HWSERIAL.println("0"); 
    if(pulse > 255 || pulse < 0) pulseSpeed = pulseSpeed * -1; 
   
    analogWrite(ledPin,pulse);

    pulse = pulse + pulseSpeed; 
  }
while (HWSERIAL.available()) {
 char inChar = (char)HWSERIAL.read();}
}
//just prints things it gets 

