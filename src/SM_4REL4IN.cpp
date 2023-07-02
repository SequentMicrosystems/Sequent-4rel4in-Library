extern "C" {
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_4REL4IN.h"

SM_4REL4IN::SM_4REL4IN(uint8_t stack)
{
	if (stack > 7)
		stack = 7;
	_hwAdd = REL4IN_SLAVE_OWN_ADDRESS_BASE + stack;
	_detected = false;
}

bool SM_4REL4IN::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(REL4IN_I2C_MEM_REVISION_MAJOR_ADD, &value))
	{
		_detected = true;
	}
	return _detected;
}

bool SM_4REL4IN::isAlive()
{
	return _detected;
}

bool SM_4REL4IN::writeRelay(uint8_t relay, bool val)
{
	if (relay > REL4IN_RELAY_CH_NO || relay == 0)
	{
		return false;
	}
	if (val)
	{
		if (OK == writeByte(REL4IN_I2C_MEM_RELAY_SET, relay))
			return true;
	}
	else
	{
		if (OK == writeByte(REL4IN_I2C_MEM_RELAY_CLR, relay))
			return true;
	}
	return false;
}

bool SM_4REL4IN::writeRelay(uint8_t val)
{
	if (OK == writeByte(REL4IN_I2C_MEM_RELAY_VAL, 0x0f & val))
		return true;
	return false;
}

int SM_4REL4IN::readOpto()
{
	int ret = 0;
	uint8_t val = 0;
	
	ret = readByte(REL4IN_I2C_MEM_DIG_IN, &val);
	if (ret < 0)
		return ret;
	return 0x0f & val;
}

bool SM_4REL4IN::readOpto(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return false;
	}
	ret = readByte(REL4IN_I2C_MEM_DIG_IN, &val);
	if (ret < 0)
		return false;
	if(val & (1 << (channel - 1)))
	{
		return true;
	}
	return false;
}

int SM_4REL4IN::readOptoAC()
{
	int ret = 0;
	uint8_t val = 0;
	
	ret = readByte(REL4IN_I2C_MEM_AC_IN, &val);
	if (ret < 0)
		return ret;
	return 0x0f & val;
}

bool SM_4REL4IN::readOptoAC(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;

	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return false;
	}
	ret = readByte(REL4IN_I2C_MEM_AC_IN, &val);
	if (ret < 0)
		return false;
	if(val & (1 << (channel - 1)))
	{
		return true;
	}
	return false;
}

bool SM_4REL4IN::readButton()
{
	int ret = 0;
	uint8_t val = 0;

	ret = readByte(REL4IN_I2C_MEM_BUTTON, &val);
	if (ret < 0)
		return false;
	if(val & 1)
	{
		return true;
	}
	return false;
}

bool SM_4REL4IN::cfgCount(uint8_t channel, bool val)
{
	uint8_t raw = 0;
	
	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return false;
	}
	if( readByte(REL4IN_I2C_MEM_EDGE_ENABLE, &raw) != 0)
	{
		return false;
	}
	if(val)
	{
		raw |= (uint8_t)1 << (channel - 1);
	}
	else
	{
		raw &= ~((uint8_t)1 << (channel - 1));
	}
	
	if( writeByte(REL4IN_I2C_MEM_EDGE_ENABLE, raw) != 0)
	{
		return false;
	}
	return true;
}

bool SM_4REL4IN::cfgCount(uint8_t val)
{
	if( writeByte(REL4IN_I2C_MEM_EDGE_ENABLE, 0x0f & val) != 0)
	{
		return false;
	}
	return true;
}

int SM_4REL4IN::readCounter(uint8_t channel)
{
	int ret = 0;
	uint32_t val = 0;

	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return -1;
	}
	ret = readDWord(REL4IN_I2C_MEM_PULSE_COUNT_START + (channel - 1) * REL4IN_COUNT_SIZE,
		&val);
	if (ret < 0)
		return ret;
	return val;
}

bool SM_4REL4IN::resetCounter(uint8_t channel)
{
	int ret = 0;
	
	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return false;
	}
	
	ret = writeByte(REL4IN_I2C_MEM_PULSE_COUNT_RESET, channel);
	if (ret < 0)
		return false;
	return true;
}

float SM_4REL4IN::readFill(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return -1;
	}
	ret = readWord(REL4IN_I2C_MEM_PWM_IN_FILL + (channel - 1) * REL4IN_PWM_IN_FILL_SIZE,
		&val);
	if (ret < 0)
		return (float)ret;
	return (float)val / REL4IN_PWM_IN_SCALE;
}

int SM_4REL4IN::readFrequency(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	if (channel < 1 || channel > REL4IN_IN_CH_NO)
	{
		return -1;
	}
	ret = readWord(REL4IN_I2C_MEM_IN_FREQENCY + (channel - 1) * REL4IN_SCAN_FREQ_SIZE,
		&val);
	if (ret < 0)
		return ret;
	return val;
}
/*
 ***************** BAS_I2C access functions ****************************
 **********************************************************************
 */
int SM_4REL4IN::writeByte(uint8_t add, uint8_t value)
{
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}

int SM_4REL4IN::writeWord(uint8_t add, uint16_t value)
{
	uint8_t buff[2];

	memcpy(buff, &value, 2);
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(buff[0]);
	Wire.write(buff[1]);
	return Wire.endTransmission();

}

int SM_4REL4IN::writeDWord(uint8_t add, uint32_t value)
{
	uint8_t buff[4];
	int i = 0;

	memcpy(buff, &value, 4);
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	for (i = 0; i < 4; i++)
	{
		Wire.write(buff[i]);
	}
	return Wire.endTransmission();

}

int SM_4REL4IN::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}

int SM_4REL4IN::readWord(uint8_t add, uint16_t *value)
{
	uint8_t buff[2];

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (2 <= Wire.available())
	{
		buff[0] = Wire.read();
		buff[1] = Wire.read();
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 2);
	return 0;
}

int SM_4REL4IN::readDWord(uint8_t add, uint32_t *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)4);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 4);
	return 0;
}

