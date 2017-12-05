/*
 * AnimationController.cpp
 *
 *  Created on: 03.07.2017
 *      Author: Lukasz
 */

#include "AnimationController.h"

AnimationController::AnimationController(uint8_t* width) {
	this->width = width;
	selectedAnimation = 0;
	colors = new CRGB[NUM_LEDS];
	speed = 10;
	currentPallete = RainbowColors_p;
	random16_add_entropy(random());
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
		case 3:
			animation3(leds);
			break;
		case 4:
			animation4(leds);
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

	if (frame < 255)
		LEDS.setBrightness(dim8_raw(frame));
	else
		LEDS.setBrightness(brighten8_raw(510 - frame));
	if (frame > 509)
		frame = 0;
	else
		frame += 1;
}

void AnimationController::animation2(CRGB* leds) {
	static uint16_t frame = 0;
	fill_palette(leds, NUM_LEDS, frame, *width, currentPallete,
			LEDS.getBrightness(), LINEARBLEND);
	if (frame > 255)
		frame = 0;
	else
		frame += 1;
}
void AnimationController::animation3(CRGB* leds) {
	static uint8_t last = 0;
	static uint8_t hue = 0;
	//leds[last] = CRGB::Black;
	//last = beatsin8(25, 0, NUM_LEDS, 0, 0);
	fill_solid(leds,NUM_LEDS,CHSV( beatsin8(25, 0, 255, 0, 0), 255, 255));
	hue += 1;
}
void AnimationController::animation4(CRGB* leds) {
	static const uint8_t SPARKING = 80;
	static const uint8_t COOLING = 100;
	static bool gReverseDirection = false;
	// Array of temperature readings at each simulation cell
	static byte heat[NUM_LEDS / 2];

	// Step 1.  Cool down every cell a little
	for (uint8_t i = 0; i < NUM_LEDS / 2; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (uint8_t k = NUM_LEDS / 2 - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < SPARKING) {
		uint8_t y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (uint8_t j = 0; j < NUM_LEDS / 2; j++) {
		CRGB color = ColorFromPalette(currentPallete,scale8(heat[j],240));
		uint8_t pixelnumber;
		if (gReverseDirection) {
			pixelnumber = (NUM_LEDS - 1) - j;
		} else {
			pixelnumber = j;
		}
		leds[pixelnumber] = color;
		leds[NUM_LEDS-(pixelnumber+1)]=color;
	}

}
void AnimationController::addSpeed(int8_t animationSpeed) {
	if (((speed + animationSpeed) > 0) && ((speed + animationSpeed) < 30))
		speed += animationSpeed;
	Serial.println(speed);
}
void AnimationController::setPalette(CRGBPalette16 pal) {
	currentPallete = pal;
}

