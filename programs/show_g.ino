#include <AcceleroMMA7361.h>

/*Simple code to show through "Serial Monitor"
of Arduino IDE real time "g"'s values of each axis.*/

AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st;

void setup()
{
  //declarar els diferents pints de l'accelerometre
  xpin = 0;   //pin per llegir l'eix x
  ypin = 1;   //pin per llegir l'eix y
  zpin = 2;   //pin per llegir l'eix z
  gs = 42;    //g select
  sl = 30;    //sleep pin: HIGH = ON, LOW = OFF
  g0 = 40;    //0g: detecta quan els 3 eixos estan a 0g (caiguda lliure)
  st = 29;    //self-test pin
  
  Serial.begin(9600);
  accelero.begin(sl, st, g0, gs, xpin, ypin, zpin); 
  accelero.setARefVoltage(3.3);                     //AREF pin de l'arduino (3.3 més precisió, sino 5)
  accelero.setSensitivity(LOW);                     //LOW = +/-6g, HIGH = +/-1,5g
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
