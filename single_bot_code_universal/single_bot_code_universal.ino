#define HWSERIAL Serial3
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h> 
int btnPin = 12; 
String botID = "01"; 
int ledPin = 10; 
int pulse = 0; 
int pulseSpeed = 1; 

//compass values 
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

float comp_x = 0;
float comp_y = 0;
float comp_z = 0;


void setup() 
{
  
  Serial.begin(9600);
  HWSERIAL.begin(9600); 
//  while(!Serial3); 
//    Serial3.println("Magnetometer Test"); Serial3.println("");
  
  /* Initialise the sensor */
  mag.enableAutoRange(true);
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  pinMode(btnPin, INPUT_PULLUP); 
}

void loop() 
{
  /* Get a new sensor event */ 

 
  
  // Calculate the angle of the vector y,x
  
  float heading = run_compass(comp_x,comp_y,comp_z);
  
  //compass values 
  int rounded = heading; 
  HWSERIAL.print(botID);
  HWSERIAL.print(" ");
  HWSERIAL.print(rounded);
  HWSERIAL.print(" ");
  //Serial.println(rounded);  
 
  HWSERIAL.print(int(comp_x));
  HWSERIAL.print(" ");
    
  HWSERIAL.print(int(comp_y));
  HWSERIAL.print(" ");

  HWSERIAL.print(int(comp_z));
  HWSERIAL.print(" ");

    Serial.print(botID);
    Serial.print(" ");
    Serial.print(int(heading));
    Serial.print(" ");
     
    Serial.print(int(comp_x));
    Serial.print(" ");
    
    Serial.print(int(comp_y));
    Serial.print(" ");

    Serial.print(int(comp_z));
    Serial.print(" ");
  
  int btn = digitalRead(btnPin); 
  delay(150); 
  
  if(btn == 0) 
  {
    HWSERIAL.println('1'); 
    Serial.println('1');
    analogWrite(ledPin,255);
  }else
  {
    HWSERIAL.println('0'); 
    Serial.println('0');
    if(pulse > 255 || pulse < 0) pulseSpeed = pulseSpeed * -1; 
   
    analogWrite(ledPin,pulse);

    pulse = pulse + pulseSpeed; 
  }
while (HWSERIAL.available()) {
 char inChar = (char)HWSERIAL.read();}
}


float run_compass(float &compass_x, float &compass_y, float &compass_z) {
  //compass code
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  compass_x = event.magnetic.x;
  compass_y = event.magnetic.y;
  compass_z = event.magnetic.z;

  // Calculate the angle of the vector y,x
  float heading = (atan2(compass_y,compass_x) * 180) / Pi;

  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  //Serial.print("Compass Heading: ");
  return heading;
}


