#include <Wire.h>
// you will need to add the libraries here from github in the "add_to_libaries_folded" to your libraries folder wherever you are keeping your Arduino sketches on your harddrive

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

#define TCAADDR 0x70 //the physical hardware address of the multiplexer

/*
  Note: this test code tests everything but the contact between two boxes. For that little trick, you have to have to boxes working. To test that, you just have to run the real code and see if it works.
*/

//bot One vars
int btn_1 = 8;
int led_1 = 9;
int IMU_1 = 3;
String botOne = "botOne";
float comp_x_1 = 0;
float comp_y_1 = 0;
float comp_z_1 = 0;


//fade code
int delayTime = 150; //set different for each ( 100, 150,200)
int ledPin = 10 ;
int pulse = 0;
int pulseSpeed = 1;

//these are for your button, imus, LED, and compass comment / uncomment as you need
// //bot Two vars
// int btn_2 = 13;
// int led_2 = 11;
// int IMU_2 = 2;
// String botTwo = "botTwo";
// float comp_x_2 = 0;
// float comp_y_2 = 0;
// float comp_z_2 = 0;
//
//
// //bot Three vars
// int btn_3 = 12;
// int led_3 = 10;
// int IMU_3 = 4;
// String botThree = "botThree";
// float comp_x_3 = 0;
// float comp_y_3 = 0;
// float comp_z_3 = 0;


/* Assign a unique ID to each IMU sensor*/
Adafruit_LSM303_Mag_Unified mag1 = Adafruit_LSM303_Mag_Unified(IMU_1);
// Adafruit_LSM303_Mag_Unified mag2 = Adafruit_LSM303_Mag_Unified(IMU_2);
// Adafruit_LSM303_Mag_Unified mag3 = Adafruit_LSM303_Mag_Unified(IMU_3);

//reads the compass details if you need them for any reason from the IMU. This is a debug function
void displaySensorDetails(Adafruit_LSM303_Mag_Unified *mag)
{
  sensor_t sensor;
  mag->getSensor(&sensor);
//  Serial.println("------------------------------------");
//  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
//  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
//  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
//  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
//  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
//  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");
//  Serial.println("------------------------------------");
//  Serial.println("");
  delay(500);
}

//cycles thorugh the addresses on the multipler
void tcaselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

float run_compass(Adafruit_LSM303_Mag_Unified *mag, float &compass_x, float &compass_y, float &compass_z) {
  //compass code
  /* Get a new sensor event */
  sensors_event_t event;
  mag->getEvent(&event);

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

//a simple range function
bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}


void setup()
{
  Serial.begin(9600); //start serial port at a baud rate of 9600
  pinMode(btn_1, INPUT_PULLUP); //set the pin for btn 1 to input pullup
  // pinMode(btn_2, INPUT_PULLUP);
  // pinMode(btn_3, INPUT_PULLUP);
  //pinMode(box1, INPUT_PULLUP);
  // pinMode(box2, INPUT_PULLUP);
  // pinMode(box3, INPUT_PULLUP);
//wtf is input pullup you might ask? basically it's an interal resistor connected to power that's pulling the button high if it's not in pressed. Otherwise, the button would be a short if it was not being pressed.

  /* Initialise the 1st sensor */
  tcaselect(IMU_1); //select the address of our 1's imu
  mag1.begin(); //start her up
  tcaselect(IMU_1); // select it again - apparently you have to do this for each command, which is annoying but how it is.
  mag1.enableAutoRange(true); //enable autoRange on the compass mangometer

  //test to make sure it acutally started, if not warn you.
  if (!mag1.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no LM303 1 detected ... Check your wiring!");
    while (1);
  }

//these chuncks of code turn on the 2, and 3rd IMUs.
  // tcaselect(IMU_2);
  // mag2.begin();
  // tcaselect(IMU_2);
  // mag2.enableAutoRange(true);
  // if (!mag2.begin())
  // {
  //   /* There was a problem detecting the HMC5883 ... check your connections */
  //   Serial.println("Ooops, no LM303 2 detected ... Check your wiring!");
  //   while (1);
  // }
  //
  // tcaselect(IMU_3);
  // mag3.begin();
  // tcaselect(IMU_3);
  // mag3.enableAutoRange(true);
  // if (!mag3.begin())
  // {
  //   /* There was a problem detecting the HMC5883 ... check your connections */
  //   Serial.println("Ooops, no LM303 3 detected ... Check your wiring!");
  //   while (1);
  // }

//  /* Display some basic information on this sensor if you're having issues. Leave this commented out normally*/
//  tcaselect(IMU);
//  displaySensorDetails(&mag1);

}


void doThing(int IMU, Adafruit_LSM303_Mag_Unified *mag, float &comp_x, float &comp_y, float &comp_z, String botID, int led, int btn){

  sensors_event_t event;
  tcaselect(IMU);
  mag->getEvent(&event);

  int heading = run_compass(mag,comp_x,comp_y,comp_z);
  Serial.print(botID);
  Serial.print(" ");
  Serial.print(heading);
  Serial.print(" ");
  Serial.print(int(comp_x));
  Serial.print(" ");
  Serial.print(int(comp_y));
  Serial.print(" ");
  Serial.print(int(comp_z));
  Serial.print(" ");
  int btnVal = digitalRead(btn);

  if(btnVal == 1)
  {
    Serial.println('0');
    analogWrite(led,255);
  }else
  {
    Serial.println('1');
    if(pulse > 255 || pulse < 0) pulseSpeed = pulseSpeed * -1;
    analogWrite(led,pulse);
    pulse = pulse + pulseSpeed;
  }

}


void loop(void)
{
//do thing is the heart of this code - it triggers all the other stuff and prints all the values for everything as one line. The last value is the button and you should see it change from 0 to 1 if it's pressed.
    doThing(IMU_1, &mag1, comp_x_1, comp_y_1, comp_z_1, "botOne", led_1, btn_1);

//    doThing(IMU_2, &mag2, comp_x_2, comp_y_2, comp_z_2, "botTwo", led_2, btn_2);
//    doThing(IMU_3, &mag3, comp_x_3, comp_y_3, comp_z_3, "botThree", led_3, btn_3);


  //just making the serial port more readable by slowing it down
  delay(50);
}
