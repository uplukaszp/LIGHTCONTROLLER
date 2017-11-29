/*
 * MemoryController.h
 *
 *  Created on: 01.07.2017
 *      Author: Lukasz
 */

#ifndef MEMORYCONTROLLER_H_
#define MEMORYCONTROLLER_H_
#include <FastLED.h>
#include <EEPROMex.h>
#include "Settings.h"
class Memory_Controller {
public:
	Memory_Controller();
	void save(CRGB *leds);
	CRGB* load();
	virtual ~Memory_Controller();
private:
};

#endif /* MEMORYCONTROLLER_H_ */
