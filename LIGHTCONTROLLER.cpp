#include <Arduino.h>
#include <FastLED.h>
#include <IRremote.h>
#include "Remote_Codes.h"
#include "Settings.h"
#include "LedsOperator.h"

IRrecv irrecv(RECV_PIN);
decode_results results;

Leds_Operator op;
codes lastCode;
void setup() {
	lastCode=0;
	op.update();
	Serial.begin(9600);
	irrecv.enableIRIn();
}
void loop() {
	 if(irrecv.decode(&results)) {
		codes c;
		if(results.value==REPEAT)
		{
			c=lastCode;
			if(c==onOff||c==Fade3)c=0xFFFFF;
			delay(500);
		}
		else
		{
			c=results.value;
		}
		lastCode=c;
		Serial.println(results.value,HEX);
		Serial.println(c,HEX);
		switch(c)
		{
		case 	brUp:
			op.incrBrightness();
			break;
		case 	brDn:
			op.decrBrightness();
			break;
		case	onOff:
			op.switchOnOff();
			break;
		case	next:
			op.load();
			break;
		case	R:
			op.setColor(CRGB::Red);
			break;
		case	R1:
		case	R2:
		case	R3:
		case	R4:
		case	RUp:
			op.incrColor(CRGB::Red);
			break;
		case	RDn:
			op.decrColor(CRGB::Red);
			break;
		case	G:
			op.setColor(CRGB::Green);
			break;
		case	G1:
		case	G2:
		case	G3:
		case	G4:
		case	GUp:
			op.incrColor(CRGB::Green);
			break;
		case	GDn:
			op.decrColor(CRGB::Green);
			break;
		case	B:
			op.setColor(CRGB::Blue);
			break;
		case	Blue1:
		case	B2:
		case	B3:
		case	B4:
		case	BUp:
			op.incrColor(CRGB::Blue);
			break;
		case	BDn:
			op.decrColor(CRGB::Blue);
			break;
		case	W:
			op.setColor(CRGB::White);
			break;
		case	W1:
		case	W2:
		case	W3:
		case	W4:
		case	Quick:
		case	Slow:
		case	Diy1:
			op.HSV();
			break;
		case	Diy2:
		case	Diy3:
		case	Diy4:
			op.HSV(true);
			break;
		case	Diy5:
		case	Diy6:
		case	Auto:
		case	Flash:
		case	Jump3:
			op.setAnimation(1);
			break;
		case	Jump7:
			op.setAnimation(2);
			break;
		case	Fade3:
			op.nextPalette();
			break;
		case	Fade7:
			op.save();
			break;
		default:
			break;
		}
		irrecv.resume();
	 }
	 if(irrecv.isIdle())
	 {
		 op.nextFrame();
		 op.update();
	 }

}

