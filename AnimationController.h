/*
 * AnimationController.h
 *
 *  Created on: 03.07.2017
 *      Author: Lukasz
 */

#ifndef ANIMATIONCONTROLLER_H_
#define ANIMATIONCONTROLLER_H_
#include <FastLED.h>
#include "Settings.h"
class AnimationController {
public:
	AnimationController(uint8_t* width);
	virtual ~AnimationController();
	void selectAnimation(uint8_t animation);
	void nextFrame(CRGB *leds);
	void selectColors(CRGB *colors);
	void addSpeed(int8_t animationSpeed);
	void setPalette(CRGBPalette16 pal);
private:
	uint8_t* width;
	void animation1(CRGB *leds);
	void animation2(CRGB *leds);
	void animation3(CRGB *leds);
	void animation4(CRGB* leds);
	void animation5(CRGB* leds);
	void animation6(CRGB* leds);
	uint8_t selectedAnimation;
	CRGB *colors;
	uint8_t speed;
	uint32_t frame;
	CRGBPalette16 currentPallete;
};

#endif /* ANIMATIONCONTROLLER_H_ */
