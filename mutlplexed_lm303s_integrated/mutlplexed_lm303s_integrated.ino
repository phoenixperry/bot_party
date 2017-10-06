#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#define TCAADDR 0x70
//data for averages 
int avBoxes1_2=0; 
int avBoxes1_3=0; 
int avBoxes2_3=0; 
int avBoxes1_2_3=20; 
int con = 20; 
//++++++++++ FILP THIS TRUE TO SKIP OVER THE CALIBATION ROUTINE 
bool calibrated = true; 
bool skipBoxes = false; 

//int delayTime = 50; 
//calibration checks 
bool started = false; 

bool boxes2_3_calibrated=false; 
bool boxes1_3_calibrated=false; 
bool boxes1_2_calibrated=false; 

//inbetween box touching state bools
bool boxes1_2; 
bool boxes1_3; 
bool boxes2_3; 
bool allConnected; 
//touches 
const int box1 = A0; 
const int box2 = A1; 
const int box3 = A2; 

//bot One vars 
int btn_1 = 8;
int led_1 = 9;
int IMU_1 = 3;
String botOne = "botOne"; 
float comp_x_1 = 0;
float comp_y_1 = 0;
float comp_z_1 = 0;

//bot Two vars 
int btn_2 = 13;
int led_2 = 11;
int IMU_2 = 2;
String botTwo = "botTwo"; 
float comp_x_2 = 0;
float comp_y_2 = 0;
float comp_z_2 = 0;


//bot Three vars 
int btn_3 = 12;
int led_3 = 10;
int IMU_3 = 4;
String botThree = "botThree"; 
float comp_x_3 = 0;
float comp_y_3 = 0;
float comp_z_3 = 0;


//fade code broken
int delayTime = 150; //set different for each ( 100, 150,200)
int ledPin = 10 ; 
int pulse = 0; 
int pulseSpeed = 1; 

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag1 = Adafruit_LSM303_Mag_Unified(IMU_1);
Adafruit_LSM303_Mag_Unified mag2 = Adafruit_LSM303_Mag_Unified(IMU_2);
Adafruit_LSM303_Mag_Unified mag3 = Adafruit_LSM303_Mag_Unified(IMU_3);

void doThing(int IMU, Adafruit_LSM303_Mag_Unified *mag, float &comp_x, float &comp_y, float &comp_z, String &botID, int &led, int &btn); 

bool inRange(int val, int minimum, int maximum);
//launches the calibration routine 
void calibrate(); 

//calibrates the boxes during the calibration routine 
int calibrateBoxes(int box_a, int box_b); 

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

bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void setup()
{
  Serial.begin(9600);
  pinMode(btn_1, INPUT_PULLUP); 
  pinMode(btn_2, INPUT_PULLUP); 
  pinMode(btn_3, INPUT_PULLUP);
  pinMode(box1, INPUT_PULLUP);
  pinMode(box2, INPUT_PULLUP);
  pinMode(box3, INPUT_PULLUP);
  
//  Serial.println("Hi");
//  Serial.println("mag Test"); Serial.println("");

  /* Initialise the 1st sensor */
  tcaselect(IMU_1);
  mag1.begin(); 
  tcaselect(IMU_1);
  mag1.enableAutoRange(true);
  if (!mag1.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no LM303 1 detected ... Check your wiring!");
    while (1);
  }

  tcaselect(IMU_2);
  mag2.begin(); 
  tcaselect(IMU_2);
  mag2.enableAutoRange(true);
  if (!mag2.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no LM303 2 detected ... Check your wiring!");
    while (1);
  }

  tcaselect(IMU_3);
  mag3.begin(); 
  tcaselect(IMU_3);
  mag3.enableAutoRange(true);
  if (!mag3.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no LM303 3 detected ... Check your wiring!");
    while (1);
  }



//  /* Display some basic information on this sensor */
//  tcaselect(IMU);
//  displaySensorDetails(&mag1);

 //calls the calibration routine 
  calibrate();  

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
  if(skipBoxes == false) 
  {   
    doThing(IMU_1, &mag1, comp_x_1, comp_y_1, comp_z_1, "botOne", led_1, btn_1);  
    doThing(IMU_2, &mag2, comp_x_2, comp_y_2, comp_z_2, "botTwo", led_2, btn_2);
    doThing(IMU_3, &mag3, comp_x_3, comp_y_3, comp_z_3, "botThree", led_3, btn_3);
       
    int ar = readTouches(box1, box2);
    
       ar = map(ar, 0, 1014, 0, 10); 
       boxes1_2 = inRange(ar, avBoxes1_2-5, avBoxes1_2+5); 
       
       Serial.print("BoxOneTwo ");
       if(boxes1_2 == 0) Serial.println(1); 
       else Serial.println(0); 
       //Serial.println(boxes1_2);
  
       ar = readTouches(box1, box3);
       ar = map(ar, 0, 1024, 0, 10); 
       boxes1_3 = inRange(ar, avBoxes1_3-5, avBoxes1_3+5); 
       Serial.print("BoxOneThree "); 
       if(boxes1_3 == 0) Serial.println(1); 
       else Serial.println(0); 
//       Serial.println(boxes1_3); 
      
       ar = readTouches(box2, box3);
       ar = map(ar, 0, 1024, 0, 10); 
       boxes2_3 = inRange(ar, avBoxes2_3-5, avBoxes2_3+5); 
      
       Serial.print("BoxTwoThree ");
       if(boxes2_3 == 0) Serial.println(1); 
       else Serial.println(0); 
//       Serial.println(boxes2_3); 

    //three boxes hack 
       
       int theseBoxes = readTouches(A0, A1);
       theseBoxes = map(theseBoxes, 0, 1024, 0, 10);     
       //Serial.println(theseBoxes); 
   
      if(boxes1_2 && boxes1_3 && boxes2_3){  
         if(theseBoxes >15) 
         {
          allConnected = true; 
         }else allConnected = false;
          
          Serial.print("AllBoxes ");
      // if(con == 20) Serial.println(1); 
       //if(allConnected == 0) Serial.println(1); 
     //  else Serial.println(0); 
        Serial.println(allConnected);
      }
       delay(delayTime); 
  }
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



