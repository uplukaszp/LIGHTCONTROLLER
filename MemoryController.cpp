/*
 * MemoryController.cpp
 *
 *  Created on: 01.07.2017
 *      Author: Lukasz
 */

#include "MemoryController.h"
Memory_Controller::Memory_Controller() {
}

void Memory_Controller::save(CRGB* leds) {

	int _address=100;
	Serial.println("save: ");
	for(int i=0;i<NUM_LEDS;i++)
	{
		EEPROM.update(_address++,leds[i].r);
		EEPROM.update(_address++,leds[i].g);
		EEPROM.update(_address++,leds[i].b);
	}
}

CRGB* Memory_Controller::load() {
	CRGB *leds=new CRGB[NUM_LEDS];
	int _address=100;
	Serial.println("load");
	for(int i=0;i<NUM_LEDS;i++)
		{
			leds[i].r=EEPROM.readByte(_address++);
			leds[i].g=EEPROM.readByte(_address++);
			leds[i].b=EEPROM.readByte(_address++);
		}

	return leds;
}

Memory_Controller::~Memory_Controller() {
	// TODO Auto-generated destructor stub
}

