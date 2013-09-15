/*=================================================================================
Program that detects a fall ensuring that it's not a "false positive" (jumps, etc).
IF a fall is detected, it waits for 10 seconds before sending a message to the 
receiver. During this time, the user can press a button to cancel this operation 
in case of a "not fatal fall".
=================================================================================*/

/*=================================================================================
This library has all the functions used in the accelerometer MMA7361.
=================================================================================*/

#include <AcceleroMMA7361.h>

/*=================================================================================
This library has all the functions used in the RF communication.
=================================================================================*/

#include <VirtualWire.h>

/*=================================================================================
Declaration of all the variables used in the program.
=================================================================================*/

AcceleroMMA7361 accelero;
float x, y, z;
int xpin, ypin, zpin, gs, sl, g0, st, interrupt_pin_number;
unsigned long start_falling_time, falling_time, start_message_time;
boolean falling, send_message;
volatile boolean cancel;

void setup()
{
  interrupt_pin_number = 2;

  /*Declare accelerometer pinout*/
  xpin = A0;   						//x axis pin
  ypin = A1;   						//y axis pin
  zpin = A2;   						//z axis pin
  gs = 5;    						//g select
  sl = 4;    						//sleep pin: HIGH = ON, LOW = OFF
  g0 = 3;    						//0g: detects free fall (HIGH when all axis = 0)
  st = 6;    						//self-test pin

  falling = false;
  send_message = false;
  cancel = false;

  Serial.begin(9600);  
  vw_setup(2000);

  /*Configurate accelerometer*/
  accelero.begin(sl, st, g0, gs, xpin, ypin, zpin); 
  accelero.setARefVoltage(3.3);                     	//arduino AREF pin (3.3 more accuracy, 5 otherwise)
  accelero.setSensitivity(LOW);                     	//LOW = +/-6g, HIGH = +/-1,5g
  accelero.calibrate();
}

void loop()
{
  get_accelerations();
  if (x<0.1 && y<0.1 && z<0.1)                   	//if all three axis are less than 0.1g, it's falling!
  {
    start_falling_time = millis();
    falling = true;
    while ((z<5 && y<5 && z<5) && falling)       	//wait for the "peak" in "g's" when it hits the ground
    {
      get_accelerations();
      falling_time = millis();
      if ((falling_time - start_falling_time)>5000)     	//if it has been falling for more than 5 seconds, its a "false positive"
      {
        falling = false;
      }
    }
    if (falling) 
    {
      wait_ten_seconds();
    }
  }
}

void wait_ten_seconds()
{
  cancel = false;
  attachInterrupt(interrupt_pin_number, cancel_send, RISING);	//the interruption will only work during the time
  start_message_time = millis();				//that the micro is "waiting" the cancel
  while ((millis() - start_message_time)<10000 && !cancel);
  detachInterrupt(interrupt_pin_number);
  if (!cancel)
  {
    send("FALL");
    falling = false;
  }
}

void get_accelerations()
{
  x = float(accelero.getXAccel())/100;
  y = float(accelero.getYAccel())/100;
  z = float(accelero.getZAccel())/100;
}

void send(char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();                                         //wait until the whole message is send
}

void cancel_send()					//interruption to cancel the sending of the message
{
  cancel = true;
}
