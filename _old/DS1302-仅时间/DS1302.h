/*
  DS1302.h - Arduino library support for the DS1302 Trickle Charge Timekeeping Chip
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
#ifndef DS1302_h
#define DS1302_h

#include "WProgram.h"

#define FORMAT_SHORT	1
#define FORMAT_LONG	2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3



#define TCR_D1R2K	165
#define TCR_D1R4K	166
#define TCR_D1R8K	167
#define TCR_D2R2K	169
#define TCR_D2R4K	170
#define TCR_D2R8K	171
#define TCR_OFF		92

class Time
{
public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
		Time();
};

class DS1302_RAM
{
public:
	byte	cell[31];

		DS1302_RAM();
};

class DS1302
{
public:
		DS1302(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin);
	Time	getTime();
	void	setTime(uint8_t hour, uint8_t min, uint8_t sec);
	

	char	*getTimeStr(uint8_t format=FORMAT_LONG);
	
	void	halt(bool value);
	void	writeProtect(bool enable);
	void	setTCR(uint8_t value);

	void		writeBuffer(DS1302_RAM r);
	DS1302_RAM	readBuffer();
	void		poke(uint8_t addr, uint8_t value);
	uint8_t		peek(uint8_t addr);

private:
	uint8_t _ce_pin;
	uint8_t _data_pin;
	uint8_t _sclk_pin;
	uint8_t _burstArray[8];

	uint8_t	_readByte();
	void	_writeByte(uint8_t value);
	uint8_t	_readRegister(uint8_t reg);
	void 	_writeRegister(uint8_t reg, uint8_t value);
	void	_burstRead();
	uint8_t	_decode(uint8_t value);
	uint8_t	_decodeH(uint8_t value);
	uint8_t	_decodeY(uint8_t value);
	uint8_t	_encode(uint8_t vaule);
};
#endif
