/*
 * AnimationController.cpp
 *
 *  Created on: 03.07.2017
 *      Author: Lukasz
 */

#include "AnimationController.h"

AnimationController::AnimationController(uint8_t* width) {
	this->width=width;
	selectedAnimation = 0;
	colors = new CRGB[NUM_LEDS];
	speed = 10;
	currentPallete=RainbowColors_p;
}

AnimationController::~AnimationController() {
}

void AnimationController::selectAnimation(uint8_t animation) {
	selectedAnimation = animation;
}

void AnimationController::nextFrame(CRGB* leds) {
	static uint8_t skipedFrame = 0;
	if (skipedFrame == speed) {
		skipedFrame = 0;
		switch (selectedAnimation) {
		case 1:
			animation1(leds);
			break;
		case 2:
			animation2(leds);
			break;
		default:
			break;
		}
	}
	skipedFrame++;
}

void AnimationController::selectColors(CRGB* colors) {
	for (int i = 0; i < NUM_LEDS; i++) {
		this->colors[i] = colors[i];
	}
}

void AnimationController::animation1(CRGB* leds) {
	static uint16_t frame = 0;

	if(frame<255)LEDS.setBrightness(dim8_raw(frame));
	else LEDS.setBrightness(brighten8_raw(510-frame));

	if (frame > 509)
		frame = 0;
	else
		frame += 1;
}

void AnimationController::animation2(CRGB* leds) {
	static uint16_t frame = 0;
	fill_palette(leds, NUM_LEDS,frame, *width, currentPallete,LEDS.getBrightness(),LINEARBLEND);
	if (frame > 255)
		frame = 0;
	else
		frame += 1;
}

void AnimationController::addSpeed(int8_t animationSpeed) {
	if(speed+animationSpeed>0&&speed+animationSpeed<10)
	speed += animationSpeed;
}
void AnimationController::setPalette(CRGBPalette16 pal)
{
	currentPallete=pal;
}

