/*
  DS1302.cpp - Arduino library support for the DS1302 Trickle Charge Timekeeping Chip
  Copyright (C)2010 Henning Karlsen. All right reserved
  
  You can find the latest version of the library at 
  http://www.henningkarlsen.com/electronics

  This library has been made to easily interface and use the DS1302 RTC with
  the Arduino.

  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Version:   1.0  - Aug   6 2010  - initial release
			 2.0  - Aug  23 2010  - Added functions to use on-chip RAM.
			 2.1  - Nov  17 2010  - Added setTCR();    

*/
#include "WProgram.h"
#include "DS1302.h"

#define REG_SEC		0
#define REG_MIN		1
#define REG_HOUR	2
#define REG_WP		7
#define REG_TCR		8

/* Public */

Time::Time()
{
	 
	this->hour = 0;
	this->min  = 0;
	this->sec  = 0;
	
}

DS1302_RAM::DS1302_RAM()
{
	for (int i=0; i<31; i++)
		cell[i]=0;
}

DS1302::DS1302(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin)
{
	_ce_pin = ce_pin;
	_data_pin = data_pin;
	_sclk_pin = sclk_pin;

	pinMode(_ce_pin, OUTPUT);
	pinMode(_sclk_pin, OUTPUT);
}

Time DS1302::getTime()
{
	Time t;
	_burstRead();
	t.sec	= _decode(_burstArray[0]);
	t.min	= _decode(_burstArray[1]);
	t.hour	= _decodeH(_burstArray[2]);
	return t;
}

void DS1302::setTime(uint8_t hour, uint8_t min, uint8_t sec)
{
	if (((hour>=0) && (hour<24)) && ((min>=0) && (min<60)) && ((sec>=0) && (sec<60)))
	{
		_writeRegister(REG_HOUR, _encode(hour));
		_writeRegister(REG_MIN, _encode(min));
		_writeRegister(REG_SEC, _encode(sec));
	}
}



char *DS1302::getTimeStr(uint8_t format)
{
	char *output= "xxxxxxxx";
	Time t;
	t=getTime();
	if (t.hour<10)
		output[0]=48;
	else
		output[0]=char((t.hour / 10)+48);
	output[1]=char((t.hour % 10)+48);
	output[2]=58;
	if (t.min<10)
		output[3]=48;
	else
		output[3]=char((t.min / 10)+48);
	output[4]=char((t.min % 10)+48);
	output[5]=58;
	if (format==FORMAT_SHORT)
		output[5]=0;
	else
	{
	if (t.sec<10)
		output[6]=48;
	else
		output[6]=char((t.sec / 10)+48);
	output[7]=char((t.sec % 10)+48);
	output[8]=0;
	}
	return output;
}



void DS1302::halt(bool enable)
{
  uint8_t _reg = _readRegister(REG_SEC);
  _reg &= ~(1 << 7);
  _reg |= (enable << 7);
  _writeRegister(REG_SEC, _reg);
}

void DS1302::writeProtect(bool enable)
{
  uint8_t _reg = (enable << 7);
  _writeRegister(REG_WP, _reg);
}

void DS1302::setTCR(uint8_t value)
{
	_writeRegister(REG_TCR, value);
}

/* Private */

uint8_t DS1302::_readByte()
{
	pinMode(_data_pin, INPUT);

	uint8_t value = 0;
	uint8_t currentBit = 0;

	for (int i = 0; i < 8; ++i)
	{
		currentBit = digitalRead(_data_pin);
		value |= (currentBit << i);
		digitalWrite(_sclk_pin, HIGH);
		delayMicroseconds(1);
		digitalWrite(_sclk_pin, LOW);
	}
	return value;
}

void DS1302::_writeByte(uint8_t value)
{
	pinMode(_data_pin, OUTPUT);
	shiftOut(_data_pin, _sclk_pin, LSBFIRST, value);
}

uint8_t DS1302::_readRegister(uint8_t reg)
{
	uint8_t cmdByte = 129;
	cmdByte |= (reg << 1);

	uint8_t readValue;

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(cmdByte);
	readValue = _readByte();
	
	digitalWrite(_ce_pin, LOW);

	return readValue;
}

void DS1302::_writeRegister(uint8_t reg, uint8_t value)
{
	uint8_t cmdByte = (128 | (reg << 1));

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(cmdByte);
	_writeByte(value);

	digitalWrite(_ce_pin, LOW);
}

void DS1302::_burstRead()
{
	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(191);
	for (int i=0; i<8; i++)
	{
		_burstArray[i] = _readByte();
	}
	digitalWrite(_ce_pin, LOW);
}

uint8_t	DS1302::_decode(uint8_t value)
{
	uint8_t decoded = value & 127;
	decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
	return decoded;
}

uint8_t DS1302::_decodeH(uint8_t value)
{
  if (value & 128)
    value = (value & 15) + (12 * ((value & 32) >> 5));
  else
    value = (value & 15) + (10 * ((value & 48) >> 4));
  return value;
}

uint8_t	DS1302::_decodeY(uint8_t value)
{
	uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
	return decoded;
}

uint8_t DS1302::_encode(uint8_t value)
{
	uint8_t encoded = ((value / 10) << 4) + (value % 10);
	return encoded;
}

void DS1302::writeBuffer(DS1302_RAM r)
{
	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(254);
	for (int i=0; i<31; i++)
	{
		_writeByte(r.cell[i]);
	}
	digitalWrite(_ce_pin, LOW);
}

DS1302_RAM DS1302::readBuffer()
{
	DS1302_RAM r;

	digitalWrite(_sclk_pin, LOW);
	digitalWrite(_ce_pin, HIGH);

	_writeByte(255);
	for (int i=0; i<31; i++)
	{
		r.cell[i] = _readByte();
	}
	digitalWrite(_ce_pin, LOW);

	return r;
}

void DS1302::poke(uint8_t addr, uint8_t value)
{
	if ((addr >=0) && (addr<=30))
	{
		addr = (addr * 2) + 192;

		digitalWrite(_sclk_pin, LOW);
		digitalWrite(_ce_pin, HIGH);

		_writeByte(addr);
		_writeByte(value);

		digitalWrite(_ce_pin, LOW);
	}
}

uint8_t DS1302::peek(uint8_t addr)
{
	if ((addr >=0) && (addr<=30))
	{
		addr = (addr * 2) + 193;

		uint8_t readValue;

		digitalWrite(_sclk_pin, LOW);
		digitalWrite(_ce_pin, HIGH);

		_writeByte(addr);
		readValue = _readByte();
		
		digitalWrite(_ce_pin, LOW);

		return readValue;
	}
	else
		return 0;
}

