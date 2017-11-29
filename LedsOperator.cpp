/*
 * LedsOperator.cpp
 *
 *  Created on: 30.06.2017
 *      Author: Lukasz
 */

#include "LedsOperator.h"

Leds_Operator::Leds_Operator() {
	leds=new CRGB[NUM_LEDS];
	palettes=new CRGBPalette16[7];
	palettes[6]=OceanColors_p;
	palettes[1]=CloudColors_p;
	palettes[2]=LavaColors_p;
	palettes[3]=ForestColors_p;
	palettes[4]=PartyColors_p;
	palettes[5]=HeatColors_p;
	palettes[0]=RainbowStripeColors_p;

	for(int i=0;i<NUM_LEDS;i++)leds[i]=CRGB::White;
	LEDS.addLeds<WS2812,DATA_PIN,GRB>(leds,NUM_LEDS);
	LEDS.setBrightness(150);
	isOn=true;
}

Leds_Operator::~Leds_Operator() {
	// TODO Auto-generated destructor stub
}

void Leds_Operator::switchOnOff() {

	setAnimation(0);
	if(isOn)
	{
		isOn=false;
		copy();
		setColor(CRGB::Black);
	}else
	{
		isOn=true;
		restore();
	}
}


void Leds_Operator::incrBrightness() {
	uint8_t brightness=LEDS.getBrightness();
	if(brightness<255)
	{
		brightness+=STEP;
		LEDS.setBrightness(brightness);
	}
}

void Leds_Operator::decrBrightness() {
	uint8_t brightness=LEDS.getBrightness();
		if(brightness>0)
		{
			brightness-=STEP;
			LEDS.setBrightness(brightness);
		}
}

void Leds_Operator::setColor(CRGB color, int pos) {
	setAnimation(0);
	if(pos==-1)
	{
		for(int i=0;i<NUM_LEDS;i++)
		{
			leds[i]=color;
		}
	}else
	{
		leds[pos]=color;
	}
}

void Leds_Operator::update() {
	LEDS.show();
}

void Leds_Operator::copy() {
	for(int i=0;i<NUM_LEDS;i++)
	{
		ledsCopy[i]=leds[i];
	}
}

void Leds_Operator::incrColor(CRGB color) {
	int temp;
	setAnimation(0);
	for(int i=0;i<NUM_LEDS;i++)
		{
			temp=leds[i].b;
			if( color.b==255)
			{
				if(temp+STEP<255)
				{
					leds[i].blue+=STEP;
				}
			}
			if(color.r==255)
			{
				temp=leds[i].r;
				if(temp+STEP<255)
				{
					leds[i].red+=STEP;
				}
			}
			if(color.g==0x80)
			{
				temp=leds[i].g;
				if(temp+STEP<255)
				{
					leds[i].green+=STEP;
				}
			}
		}
}

void Leds_Operator::decrColor(CRGB color) {
	int temp;
	setAnimation(0);
	for(int i=0;i<NUM_LEDS;i++)
	{

		if( color.b==255)
		{
			temp=leds[i].b;
			if(temp-STEP>0)
			{
				leds[i].blue-=STEP;
			}
		}
		if(color.r==255)
		{
			temp=leds[i].r;
			if(temp-STEP>0)
			{
				leds[i].red-=STEP;
			}
		}
		if(color.g==0x80)
		{
			temp=leds[i].g;
			if(temp-STEP>0)
			{
				leds[i].green-=STEP;
			}
		}
	}
}

void Leds_Operator::load() {
	setAnimation(0);
	delete leds;
	leds=mem.load();
}

void Leds_Operator::save() {
	mem.save(leds);
}

void Leds_Operator::HSV(bool reverse) {
	static int initHue=0;

	if(!reverse)initHue+=255/NUM_LEDS;
	else initHue-=255/NUM_LEDS;
	setAnimation(0);
	fill_rainbow(leds, NUM_LEDS, initHue, 255/NUM_LEDS);

}

void Leds_Operator::setAnimation(uint8_t animation) {
	anim.selectAnimation(animation);
	anim.selectColors(leds);
}

void Leds_Operator::nextFrame() {
	anim.nextFrame(leds);
}

void Leds_Operator::nextPalette() {
	setAnimation(0);
	static uint8_t pal=0;
	uint8_t start=0;
	for(int i=0;i<NUM_LEDS;i++)
	{
		leds[i]=ColorFromPalette(palettes[pal], start, 255, NOBLEND);
		start+=3;
	}

	if(pal>6)pal=0;
	pal++;
}

void Leds_Operator::restore() {
	for(int i=0;i<NUM_LEDS;i++)
	{
		leds[i]=ledsCopy[i];
	}
}
