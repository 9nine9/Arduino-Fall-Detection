#include <AcceleroMMA7361.h>


AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st;
unsigned long temps_inici, temps_caient;
boolean caient;


void setup()
{
  //declarar els diferents pints de l'accelerometre
  xpin = A0;   //pin per llegir l'eix x
  ypin = A1;   //pin per llegir l'eix y
  zpin = A2;   //pin per llegir l'eix z
  gs = 5;    //g select
  sl = 4;    //sleep pin: HIGH = ON, LOW = OFF
  g0 = 3;    //0g: detecta quan els 3 eixos estan a 0g (caiguda lliure)
  st = 6;    //self-test pin
  caient = false;
  
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
  if (x<0.1 && y<0.1 && z<0.1)
  {
    temps_inici = millis();
    caient = true;
  }
  if (caient);
  {
    while ((z<5 && y<5 && z<5) && caient)
    {
      x = float(accelero.getXAccel())/100;
      y = float(accelero.getYAccel())/100;
      z = float(accelero.getZAccel())/100;
      temps_caient = millis();
      if ((temps_caient - temps_inici)>5000)
      {
        caient = false;
      }
    }
    if (caient) Serial.println("CAIGUDA");
    caient = false;
  }
}
