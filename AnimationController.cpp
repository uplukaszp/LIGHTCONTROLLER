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
	frame=0;
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
			break;
		case 5:
			animation5(leds);
			break;
		case 6:
			animation6(leds);
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

	fill_palette(leds, NUM_LEDS, frame, *width, currentPallete,
	LEDS.getBrightness(), LINEARBLEND);
	if (frame > 255)
		frame = 0;
	else
		frame += 1;
}
void AnimationController::animation3(CRGB* leds) {
	static uint8_t gHue = 0;
	EVERY_N_MILLISECONDS(20) {
		gHue++;
	};
	fadeToBlackBy(leds, NUM_LEDS, 20);
	uint8_t pos = map(sin8(frame),0,255,0,NUM_LEDS-1);
	leds[pos] += CHSV(gHue, 255, 192);
	frame++;
}
void AnimationController::animation4(CRGB* leds) {
	static const uint8_t SPARKING = 80;
	static const uint8_t COOLING = 100;
	static bool gReverseDirection = false;
	static byte heat[NUM_LEDS / 2];
	for (uint8_t i = 0; i < NUM_LEDS / 2; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
	}
	for (uint8_t k = NUM_LEDS / 2 - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}
	if (random8() < SPARKING) {
		uint8_t y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}
	for (uint8_t j = 0; j < NUM_LEDS / 2; j++) {
		CRGB color = HeatColor(heat[j]);
		uint8_t pixelnumber;
		if (gReverseDirection) {
			pixelnumber = (NUM_LEDS - 1) - j;
		} else {
			pixelnumber = j;
		}
		leds[pixelnumber]=blend(leds[pixelnumber], color,128);
		leds[NUM_LEDS - (pixelnumber+2)]=blend(leds[NUM_LEDS - (pixelnumber+2)],color,128);
	}


}
void AnimationController::animation5(CRGB* leds) {
	fadeToBlackBy(leds, NUM_LEDS, 40);
	byte dothue = 0;
	for (int i = 0; i < 4; i++) {
		leds[map(sin8(i*frame++),0,255,0,NUM_LEDS-1)] |= CHSV(dothue, 200, 255);
		dothue += 66;
	}
}
void AnimationController::animation6(CRGB* leds) {
	uint16_t xscale = 30; // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
	uint16_t yscale = 30;
	static int16_t dist = random16();
	for (int i = 0; i < 20; i++) {
		uint8_t locn = inoise8(xscale, dist + yscale + i * 200); // Get a new pixel location from moving noise. locn rarely goes below 48 or above 192, so let's remove those ends.
		locn = constrain(locn, 48, 192); // Ensure that the occasional value outside those limits is not used.
		uint8_t pixlen = map(locn, 48, 192, 0, NUM_LEDS - 1); // Map doesn't constrain, so we now map locn to the the length of the strand.
		locn=map(locn,48,192,0,255);
		leds[pixlen] = ColorFromPalette(currentPallete, inoise8(dist), 255,LINEARBLEND); // Use that value for both the location as well as the palette index colour for the pixel.
	}

	dist += map(sin8(frame++),0,255,1,4);
	fadeToBlackBy(leds, NUM_LEDS, 16);
}
void AnimationController::addSpeed(int8_t animationSpeed) {
	if (((speed + animationSpeed) > 0) && ((speed + animationSpeed) < 30))
		speed += animationSpeed;
	Serial.println(speed);
}
void AnimationController::setPalette(CRGBPalette16 pal) {
	currentPallete = pal;
}

