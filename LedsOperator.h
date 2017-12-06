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
	void setAnimation(uint8_t animation);
	void nextFrame();
	void nextPalette();
	uint8_t getPaletteWidth();
	void setPaletteWidth(uint8_t);
	uint8_t getPaletteShift();
	void setPaletteShift(uint8_t);
	void addSpeed(int8_t animationSpeed);
private:
	uint8_t palleteShift=0;
	uint8_t paletteWidth=5;
	uint8_t pal=-1;
	Memory_Controller mem;
	AnimationController anim;
	void copy();
	void restore();
	CRGB *leds;
	CRGB ledsCopy[NUM_LEDS];
	bool isOn;
	CRGBPalette16 *palettes;
};

