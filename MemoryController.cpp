/*
 * MemoryController.cpp
 *
 *  Created on: 01.07.2017
 *      Author: Lukasz
 */

#include "MemoryController.h"
Memory_Controller::Memory_Controller() {
	EEPROM.setMaxAllowedWrites(1000);
}

void Memory_Controller::save(CRGB* leds) {

	int _address=1;
	Serial.println("save: ");
	for(int i=0;i<NUM_LEDS;i++)
	{
		Serial.print("\ntoSaveR:");
		Serial.print(leds[i].r);
		Serial.print("\t Saved: ");

		EEPROM.update(_address++,leds[i].r);
		Serial.print(EEPROM.readByte(_address-1));
		Serial.print("\ntoSaveG:");
		Serial.print(leds[i].g);
		Serial.print("\t Saved: ");
		EEPROM.update(_address++,leds[i].g);
		Serial.print(EEPROM.readByte(_address-1));
		Serial.print("\ntoSaveB:");
		Serial.print(leds[i].b);
		Serial.print("\t Saved: ");
		EEPROM.update(_address++,leds[i].b);
		Serial.print(EEPROM.readByte(_address-1));
	}
}

CRGB* Memory_Controller::load() {
	CRGB *leds=new CRGB[NUM_LEDS];
	int _address=1;
	Serial.println("load");
	for(int i=0;i<NUM_LEDS;i++)
		{
			leds[i].r=EEPROM.readByte(_address++);
			Serial.print("\nReadedR:");
			Serial.print(leds[i].r);
			leds[i].g=EEPROM.readByte(_address++);
			Serial.print("\tReadedG:");
			Serial.print(leds[i].g);
			leds[i].b=EEPROM.readByte(_address++);
			Serial.print("\tReadedB:");
			Serial.print(leds[i].b);
		}

	return leds;
}

Memory_Controller::~Memory_Controller() {
	// TODO Auto-generated destructor stub
}

