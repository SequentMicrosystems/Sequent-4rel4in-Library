/*!
 * @file SM_4REL4IN.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * Four Relays four HV Inputs 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/collections/all-io-cards/products/four-relays-four-inputs-for-raspberry-pi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems 
 *  
 */
#ifndef __SM_4REL4IN__
#define __SM_4REL4IN__

#define REL4IN_RELAY_CH_NO 4
#define REL4IN_LED_CH_NO 4
#define REL4IN_IN_CH_NO 4
#define REL4IN_COUNT_SIZE 4
#define REL4IN_ENC_COUNT_SIZE 4
#define REL4IN_ENC_NO 2
#define REL4IN_SCAN_FREQ_SIZE 2
#define REL4IN_PWM_IN_FILL_SIZE 2
#define REL4IN_PWM_IN_SCALE 100
#define REL4IN_IN_FREQENCY_SIZE 2

#define OK 0

#define REL4IN_SLAVE_OWN_ADDRESS_BASE 0x0e

enum
{
	REL4IN_I2C_MEM_RELAY_VAL = 0,
	REL4IN_I2C_MEM_RELAY_SET,
	REL4IN_I2C_MEM_RELAY_CLR,
	REL4IN_I2C_MEM_DIG_IN,
	REL4IN_I2C_MEM_AC_IN,
	REL4IN_I2C_MEM_LED_VAL,
	REL4IN_I2C_MEM_LED_SET,
	REL4IN_I2C_MEM_LED_CLR,
	REL4IN_I2C_MEM_LED_MODE, //0-auto, 1 - manual;
	REL4IN_I2C_MEM_EDGE_ENABLE,
	REL4IN_I2C_MEM_ENC_ENABLE,
	REL4IN_I2C_MEM_SCAN_FREQ,
	REL4IN_I2C_MEM_PULSE_COUNT_START = REL4IN_I2C_MEM_SCAN_FREQ + REL4IN_SCAN_FREQ_SIZE,
	REL4IN_I2C_MEM_PPS = REL4IN_I2C_MEM_PULSE_COUNT_START + (REL4IN_IN_CH_NO * REL4IN_COUNT_SIZE),
	REL4IN_I2C_MEM_ENC_COUNT_START = REL4IN_I2C_MEM_PPS + REL4IN_IN_CH_NO * REL4IN_IN_FREQENCY_SIZE,
	REL4IN_I2C_MEM_PWM_IN_FILL = REL4IN_I2C_MEM_ENC_COUNT_START + (REL4IN_ENC_NO * REL4IN_ENC_COUNT_SIZE),
	REL4IN_I2C_MEM_IN_FREQENCY = REL4IN_I2C_MEM_PWM_IN_FILL + (REL4IN_IN_CH_NO * REL4IN_PWM_IN_FILL_SIZE),
	REL4IN_I2C_MEM_IN_FREQENCY_END = REL4IN_I2C_MEM_IN_FREQENCY + (REL4IN_IN_CH_NO * REL4IN_IN_FREQENCY_SIZE) - 1,
	REL4IN_I2C_MEM_PULSE_COUNT_RESET,//2 bytes to be one modbus register
	REL4IN_I2C_MEM_ENC_COUNT_RESET = REL4IN_I2C_MEM_PULSE_COUNT_RESET + 2,//2 bytes to be one modbus register
	REL4IN_I2C_MODBUS_SETINGS_ADD = REL4IN_I2C_MEM_ENC_COUNT_RESET + 2,
	REL4IN_I2C_NBS1,
	REL4IN_I2C_MBS2,
	REL4IN_I2C_MBS3,
	REL4IN_I2C_MODBUS_ID_OFFSET_ADD,
	REL4IN_I2C_MEM_EXTI_ENABLE,
	REL4IN_I2C_MEM_BUTTON, //bit0 - state, bit1 - latch


	REL4IN_I2C_MEM_REVISION_HW_MAJOR_ADD = 0x78,
	REL4IN_I2C_MEM_REVISION_HW_MINOR_ADD,
	REL4IN_I2C_MEM_REVISION_MAJOR_ADD,
	REL4IN_I2C_MEM_REVISION_MINOR_ADD,

};

/*!
 * @brief SM_4REL4IN class
 */
class SM_4REL4IN
{
public:

    /*!
	 * @brief Class constructor.
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
	

private:
	uint8_t _hwAdd;
	bool _detected;
	int writeByte(uint8_t add, uint8_t value);
	int writeWord(uint8_t add, uint16_t value);
	int writeDWord(uint8_t add, uint32_t value);
	int readByte(uint8_t add, uint8_t* value);
	int readWord(uint8_t add, uint16_t* value);
	int readDWord(uint8_t add, uint32_t* value);
};

#endif //__SM_4REL4IN__
