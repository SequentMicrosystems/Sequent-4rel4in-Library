/*!
    Relay usage example for Sequent Microsystems Four Relays four HV Inputs HAT
    -->https://github.com/SequentMicrosystems/Sequent-4rel4in-Library
    Requirments: Any arduino card with I2C, Four Relays four HV Inputs HAT from Sequent Microsystems


    Method 1:
      Connect I2C bus, 5V and GND from Arduino card to Four Relays four HV Inputs hat, pin map below
     SIGNAL  CONNECTOR    SIGNAL\n
      ---------------------------
           -- 1|O O| 2--  +5V
   I2C SDA -- 3|O O| 4--  +5V
   I2C SCL -- 5|O O| 6--  GND
           -- 7|O O| 8--
       GND -- 9|O O|10--
           --11|O O|12--
           --13|O O|14--  GND
           --15|O O|16--
           --17|O O|18--
           --19|O O|20--  GND
           --21|O O|22--
           --23|O O|24--
       GND --25|O O|26--
           --27|O O|28--
           --29|O O|30--  GND
           --31|O O|32--
           --33|O O|34--  GND
           --35|O O|36--
           --37|O O|38--
       GND --39|O O|40--

    Method 2:
    Use sequent Microsystems Uno, Nano, Teensy,Feather, ESP32 Raspberry Pi Replacement Kit with prefered arduino processor
    -->https://sequentmicrosystems.com/collections/accessories/products/raspberry-pi-replacement-card

    Method 3:
     Use Sequent Microsysstems ESP32 Pi replacement connected directly with the Four Relays four HV Inputs card.
     Set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1
	 -->https://sequentmicrosystems.com/collections/all-io-cards/products/esp32-pi-low-cost-replacement-for-raspberry-pi

  
    Push the card button to here the relays music:)

*/
#include "SM_4REL4IN.h"

SM_4REL4IN card(0);// Four Relays four HV Inputs HAT with stack level 0 (no jumpers installed)

void setup() {
  Serial.begin(115200);
  delay(2000);

  if (card.begin() )
  {
    Serial.print("Four Relays four HV Inputs Card detected\n");
  }
  else
  {
    Serial.print("Four Relays four HV Inputs Card NOT detected!\n");
  }

}

void loop() {
  if (card.isAlive() )
  {
	if(card.readButton())
	{		
      for (int i = 1; i < 5; i++)
      {
        card.writeRelay(i, 1);
        delay(250);
      }
      for (int i = 1; i < 5; i++)
      {
        card.writeRelay(i, 0);
        delay(250);
      }
	}
    delay(250);
  }
}
