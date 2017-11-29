/*
 * LedsOperator.h
 *
 *  Created on: 30.06.2017
 *      Author: Lukasz
 */


#include <FastLED.h>
#include "Settings.h"
#include "MemoryController.h"
#include "AnimationController.h"
class Leds_Operator {
public:
	Leds_Operator();
	virtual ~Leds_Operator();
	void switchOnOff();
	void incrBrightness();
	void decrBrightness();
	void setColor(CRGB color,int pos=-1);
	void incrColor(CRGB color);
	void decrColor(CRGB color);
	void update();
	void load();
	void save();
	void HSV(bool reverse=false);
	void setAnimation(uint8_t animation);
	void nextFrame();
	void nextPalette();
private:
	Memory_Controller mem;
	AnimationController anim;
	void copy();
	void restore();
	CRGB *leds;
	CRGB ledsCopy[NUM_LEDS];
	bool isOn;
	CRGBPalette16 *palettes;
};

