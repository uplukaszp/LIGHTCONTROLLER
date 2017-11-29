/*
 * AnimationController.cpp
 *
 *  Created on: 03.07.2017
 *      Author: Lukasz
 */

#include "AnimationController.h"

AnimationController::AnimationController() {
	selectedAnimation=0;
	colors=new CRGB[NUM_LEDS];

}

AnimationController::~AnimationController() {
}

void AnimationController::selectAnimation(uint8_t animation) {
	selectedAnimation=animation;
}

void AnimationController::nextFrame(CRGB* leds) {
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

void AnimationController::selectColors(CRGB* colors) {
	for(int i=0;i<NUM_LEDS;i++)
		{
			this->colors[i]=colors[i];
		}
}

void AnimationController::animation1(CRGB* leds) {
	static uint16_t frame=0;
	for(int i=0;i<NUM_LEDS;i++)
	{
		CHSV temp=rgb2hsv_approximate(colors[i]);
		if(frame<255)temp.v=brighten8_lin(frame);
		else temp.v=brighten8_lin(510-frame);
		leds[i]=temp;
	}
    if(frame>509)frame=0;
    else frame++;
}

void AnimationController::animation2(CRGB* leds) {
	static uint16_t frame=0;
	fill_rainbow(leds, NUM_LEDS, frame, 255/NUM_LEDS);
    if(frame>255)frame=0;
    else frame++;
}
