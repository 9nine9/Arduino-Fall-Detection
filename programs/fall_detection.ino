#include <AcceleroMMA7361.h>


AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st;
boolean caiguda;

void interrupt_name() //interrupcio que s'activa si es detecten 0g als 3 eixos
{
  //pensar que fer si detecta caiguda
}

void fall() //funcio per si es detecta caiguda sense fer servir interrupcions
{
  //pensar que fer si detecta caiguda
}

void setup()
{
  //declarar els diferents pints de l'accelerometre i altres variables
  xpin = 0;   //pin per llegir l'eix x
  ypin = 1;   //pin per llegir l'eix y
  zpin = 2;   //pin per llegir l'eix z
  gs = 42;    //g select
  sl = 30;    //sleep pin: HIGH = ON, LOW = OFF
  g0 = 2;    //0g: detecta quan els 3 eixos estan a 0g (caiguda lliure) (ha de ser 2 o 3 per poder ser interrupcio)
  st = 29;    //self-test pin
  caiguda = false;
  
  //interrupcio "interrupt_name" que saltara quan el pin g0 canvii de LOW a HIGH
  attatchInterrupt(0,interrupt_name,RISING);
  
  //configurar accelerometre
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
  if (x>2 && y>2 && z>2) //vigila que no hi hagi una frenada brusca (en comptes de 0g, busca >2g)
  {
    caiguda = true; //pensar que fer si detecta caiguda

  }
  
  /*
  Serial.print("\nx: ");
  Serial.print(x);
  Serial.print(" \ty: ");
  Serial.print(y);
  Serial.print(" \tz: ");
  Serial.print(z);
  delay(500);     */
}
