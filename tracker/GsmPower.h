/*
   Copyright (C) 2018 SFini

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
  * @file GsmPower.h
  * 
  * Power switch to the sim808 module.
  */


/**
  * Class to switch on/off the DC-DC modul LM2596.
  */
class MyGsmPower
{
protected:
   MyData &myData;          //!< Reference to the data

   int     pinPower;        //!< esp8266 pin connected with pin 5 of the LM2596 modul. 
   long    powerOnStartSec; //!< Timestamp of power on.
      
public:
   MyGsmPower(MyData &data, int pin);
   
   bool begin();

   void on();
   void off();   
};

/* ******************************************** */

/** Constructor */
MyGsmPower::MyGsmPower(MyData &data, int pin)
   : myData(data)
   , pinPower(pin)
   , powerOnStartSec(0)
{
}

/** Set the pin mode to input -> switch off the DC-DC module */
bool MyGsmPower::begin()
{
   MyDbg(F("MyGsmPower::begin"));
   pinMode(pinPower, INPUT);
   return true;
}

/** Switch on the DC-DC module */
void MyGsmPower::on()
{
   MyDbg(F("MyGsmPower::on"));
   pinMode(pinPower, OUTPUT);
   digitalWrite(pinPower, LOW); 
   myData.isPowerOn = true;
   powerOnStartSec  = millis() / 1000;
   MyDelay(1000);
}

/** Switch off the DC-DC module */
void MyGsmPower::off()
{
   MyDbg(F("MyGsmPower::off"));
   pinMode(pinPower, INPUT);
   digitalWrite(pinPower, HIGH); 
   myData.rtcData.powerOnTimeSec += millis() / 1000 - powerOnStartSec;
   myData.isPowerOn = false;
   powerOnStartSec = 0;
}
