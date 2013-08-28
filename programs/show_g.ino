#include <AcceleroMMA7361.h>

/*Simple code to show through "Serial Monitor"
of Arduino IDE real time "g"'s values of each axis.*/

AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st;

void setup()
{
  xpin = 0;   
  ypin = 1;   
  zpin = 2; 
  gs = 42;  
  sl = 30;    
  g0 = 40;    
  st = 29;    
  
  Serial.begin(9600);
  accelero.begin(sl, st, g0, gs, xpin, ypin, zpin); 
  accelero.setARefVoltage(3.3);                     
  accelero.setSensitivity(LOW);                    
  accelero.calibrate();
}

void loop()
{
  x = float(accelero.getXAccel())/100;
  y = float(accelero.getYAccel())/100;
  z = float(accelero.getZAccel())/100;
  Serial.print("\nx: ");
  Serial.print(x);
  Serial.print(" \ty: ");
  Serial.print(y);
  Serial.print(" \tz: ");
  Serial.print(z);
  delay(500);                                     
}
