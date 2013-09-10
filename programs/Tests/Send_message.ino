/*========================================
Program that sends via MX-FS-03V (RF) a 
message when it receives an external
signal.
========================================*/

/*========================================
This library has all the functions used in
the RF communication.
========================================*/

#include <VirtualWire.h>

/*========================================
Declaration of all the variables used in
the program.
========================================*/



void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
}

void loop()
{
  send("Hello there");
  delay(1000);
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

