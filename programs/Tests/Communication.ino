/*========================================
Program that sends via Serial Monitor a 
message when it receives an external
signal.
========================================*/

/*========================================
This library has all the functions used in
the accelerometer MMA7361.
========================================*/

#include <AcceleroMMA7361.h>

/*========================================
Declaration of all the variables used in
the program.
========================================*/

AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st;
unsigned long start_time, falling_time;
boolean falling;


void setup()
{
  //Declare accelerometer pinout
  xpin = A0;   //x axis pin
  ypin = A1;   //y axis pin
  zpin = A2;   //z axis pin
  gs = 5;    //g select
  sl = 4;    //sleep pin: HIGH = ON, LOW = OFF
  g0 = 3;    //0g: detects free fall (HIGH when all axis = 0)
  st = 6;    //self-test pin
  falling = false;
  
  Serial.begin(9600);
  accelero.begin(sl, st, g0, gs, xpin, ypin, zpin); 
  accelero.setARefVoltage(3.3);                     //arduino AREF pin (3.3 more accuracy, 5 otherwise)
  accelero.setSensitivity(LOW);                     //LOW = +/-6g, HIGH = +/-1,5g
  accelero.calibrate();
}

void loop()
{
  
}

