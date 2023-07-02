# Sequent-4rel4in-Library
Arduino library for Sequent Microsystems [Four Relays four HV Inputs 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/four-relays-four-inputs-for-raspberry-pi)

## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *SM_4RELAY* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/Sequent-4rel4in-Library/archive/refs/heads/main.zip) button from the main [page](https://github.com/SequentMicrosystems/Sequent-4rel4in-Library), rename the uncompressed folder to "SM_4RELAY" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see SM_4RELAY inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > SM_4RELAY > and chose your example to run.

## Usage
There are three ways to control the Four Relays four HV Inputs Card from the Arduino environment.

### Method 1: Using any Arduino controller
You can use this method with any Arduino card with an I2C port by connecting I2C-SDA, I2C-SCL, +5V and GND, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C-SDA | --3| O - O | 4-- |  +5V |
| I2C-SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs using Uno, Nano, Teensy, Feather or ESP32. Plug the Four Relays four HV Inputs HAT into the 40 pin connector of the adapter and write your Arduino software.

### Method 3: Using the [SM ESP32-Pi Raspberry Pi Alternative Card](https://sequentmicrosystems.com/collections/all-io-cards/products/esp32-pi-low-cost-replacement-for-raspberry-pi)
ESP32-Pi is a Raspberry Pi alternate solution which can control directly the Four Relays four HV Inputs HAT.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1

## Function prototypes
 
         /*!
	 * @brief Class constructor.
         * @param stack - The stack level of the card, choosed with the jumpers
	 */
	SM_4REL4IN(uint8_t stack = 0);
 
	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	/*!
	 * @brief Set one relay state
	 * @param relay -  Relay number 1..4 as are printed on the card
	 * @param val The new state of the relay, true: energised
	 * @return Returns true if successful
	 */
	bool writeRelay(uint8_t relay, bool val);

	/*!
	 * @brief Write all relays state as a 4 bits bitmap
	 * @param val The bitmap of the relays states
	 * @return Returns true if successful
	 */
	bool writeRelay(uint8_t val);

    /*!
	 * @brief Read optically isolated ports as a bitmap.
	 * @return the state of all opto inputs
	 */
	int readOpto();

	/*!
	 * @brief Read one optically isolated channel.
	 * @param channel [1..4]
	 * @return the state of one  optically isolated channel
	 */
	bool readOpto(uint8_t channel);
	
	/*!
	 * @brief Read optically isolated ports as a bitmap, when signal is AC.
	 * @return the state of all opto inputs, filtred.
	 */
	int readOptoAC();

	/*!
	 * @brief Read one optically isolated channel, when signal is AC.
	 * @param channel [1..4]
	 * @return the state of one  optically isolated channel, filtred to detect AC signals
	 */
	bool readOptoAC(uint8_t channel);
	
	 /*!
	 * @brief Read button current state.
	 * @return true - pushed; false - released.
	 */
	bool readButton();
	
	/*!
	 * @brief Enable/Disable the counting function for one input channel
	 * @param channel -  Input channel number 1..4 as are printed on the card
	 * @param val The new state of the counting function settings, true: enabled, false: disabled
	 * @return Returns true if successful
	 */
	bool cfgCount(uint8_t channel, bool val);

	/*!
	 * @brief Enable/Disable the counting function for all inputs as a 4 bits bitmap (1-enable, 0-disable for each channel)
	 * @param val The bitmap of the counting function states
	 * @return Returns true if successful
	 */
	bool cfgCount(uint8_t val);
	
	/*!
	 * @brief Read the counter for a channel
	 * @param channel -  Input channel number 1..4 as are printed on the card
	 * @return number of transitions counted for the respective channel.
	 */
	int readCounter(uint8_t channel);
	
	/*!
	 * @brief Reset the acumulated transitions count for a channel
	 * @param channel -  Input channel number 1..4 as are printed on the card
	 * @return Returns true if successful
	 */
	bool resetCounter(uint8_t channel);
	
	/*!
	 * @brief Read the fill factor for a PWM signal aplyed to an input channel
	 * @param channel -  Input channel number 1..4 as are printed on the card
	 * @return fill factor 0 .. 100.
	 */
	float readFill(uint8_t channel);
	
	/*!
	 * @brief Read the frequency for a signal aplyed to an input channel
	 * @param channel -  Input channel number 1..4 as are printed on the card
	 * @return frequency in Hz
	 */
	int readFrequency(uint8_t channel);
	
	
