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
	AnimationController();
	virtual ~AnimationController();
	void selectAnimation(uint8_t animation);
	void nextFrame(CRGB *leds);
	void selectColors(CRGB *colors);
private:
	void animation1(CRGB *leds);
	void animation2(CRGB *leds);
	uint8_t selectedAnimation;
	CRGB *colors;
};

#endif /* ANIMATIONCONTROLLER_H_ */
