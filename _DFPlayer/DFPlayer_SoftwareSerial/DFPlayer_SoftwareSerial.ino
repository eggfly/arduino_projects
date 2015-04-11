/*******************************************************************************
 * DFPlayer_Mini_Mp3, This library provides a quite complete function for      * 
 * DFPlayer mini mp3 module.                                                   *
 * www.github.com/dfrobot/DFPlayer_Mini_Mp3 (github as default source provider)*
 *  DFRobot-A great source for opensource hardware and robot.                  *
 *                                                                             *
 * This file is part of the DFplayer_Mini_Mp3 library.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is free software: you can redistribute it and/or          *
 * modify it under the terms of the GNU Lesser General Public License as       *
 * published by the Free Software Foundation, either version 3 of              *
 * the License, or any later version.                                          *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * DFPlayer_Mini_Mp3 is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU Lesser General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public            *
 * License along with DFPlayer_Mini_Mp3. If not, see                           *
 * <http://www.gnu.org/licenses/>.                                             *
 *									       *
 ******************************************************************************/

/*
 *	Copyright:	DFRobot
 *	name:		DFPlayer_Mini_Mp3 sample code
 *	Author:		lisper <lisper.li@dfrobot.com>
 *	Date:		2014-05-30
 *	Description:	connect DFPlayer Mini by SoftwareSerial, this code is test on Uno
 *			Note: the mp3 files must put into mp3 folder in your tf card 
 */
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int volume = 20;
void setup () {
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
  delay(100);
  mp3_set_volume (volume);
  delay(100);
}


int status = 0;
void loop () {
  if (status == 0) {
    mp3_play();
    delay(100);
    status = 1;
  }
}
void printMenu() {
  Serial.println("----------------------");
  Serial.println("n: next song");
  Serial.println("p: previous song");
  Serial.println("r: start random play");
  Serial.println("+ or =: volume +");
  Serial.println("- or _: volume -");
  Serial.println("---------------------");
  Serial.println("please enter:");
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    switch(inChar) {
    case '+':
    case '=':
      volume++;
      mp3_set_volume (volume);
      Serial.print(volume, DEC);
      Serial.println();
      printMenu();
      break;
    case '-':
    case '_':
      volume--;
      mp3_set_volume (volume);
      Serial.print(volume, DEC);
      Serial.println();
      printMenu();
      break;
    case 'n':
      mp3_next();
      Serial.println("next song");
      printMenu();
      break;
    case 'p':
      mp3_prev();
      Serial.println("previous song");
      printMenu();
      break;
    case 'r':
      mp3_random_play();
      Serial.println("random play");
      printMenu();
      break;
    case '\n':
      printMenu();
      break;
    }
  }
}

/*
   mp3_play ();		//start play
 mp3_play (5);	//play "mp3/0005.mp3"
 mp3_next ();		//play next 
 mp3_prev ();		//play previous
 mp3_set_volume (uint16_t volume);	//0~30
 mp3_set_EQ ();	//0~5
 mp3_pause ();
 mp3_stop ();
 void mp3_get_state (); 	//send get state command
 void mp3_get_volume (); 
 void mp3_get_u_sum (); 
 void mp3_get_tf_sum (); 
 void mp3_get_flash_sum (); 
 void mp3_get_tf_current (); 
 void mp3_get_u_current (); 
 void mp3_get_flash_current (); 
 void mp3_single_loop (boolean state);	//set single loop 
 void mp3_DAC (boolean state); 
 void mp3_random_play (); 
 */













