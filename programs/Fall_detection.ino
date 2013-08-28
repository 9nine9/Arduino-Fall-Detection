/*=======================================
Program that detects a fall ensuring that
it's not a "false positive" (jumps, etc).
========================================*/

#include <AcceleroMMA7361.h>

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
  x = float(accelero.getXAccel())/100;
  y = float(accelero.getYAccel())/100;
  z = float(accelero.getZAccel())/100;
  if (x<0.1 && y<0.1 && z<0.1)
  {
    start_time = millis();
    falling = true;
  }
  if (falling);
  {
    while ((z<5 && y<5 && z<5) && falling)
    {
      x = float(accelero.getXAccel())/100;
      y = float(accelero.getYAccel())/100;
      z = float(accelero.getZAccel())/100;
      falling_time = millis();
      if ((falling_time - start_time)>5000)
      {
        falling = false;
      }
    }
    if (falling) Serial.println("FALL!");
    falling = false;
  }
}
