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
	lastCode = 0;
	op.update();
	Serial.begin(9600);
	irrecv.enableIRIn();
}
void loop() {
	if (irrecv.decode(&results)) {
		codes c;
		if (results.value == REPEAT) {
			c = lastCode;
			if (c == onOff || c == Fade3)
				c = 0xFFFFF;
			delay(200);
		} else {
			c = results.value;
		}
		lastCode = c;
		Serial.println(results.value, HEX);
		Serial.println(c, HEX);
		switch (c) {
		case brUp:
			op.incrBrightness();
			break;
		case brDn:
			op.decrBrightness();
			break;
		case onOff:
			op.switchOnOff();
			break;
		case next:
			op.load();
			break;
		case R:
			op.setColor(CRGB::Red);
			break;
		case R1:
			op.setColor(CRGB::IndianRed);
			break;
		case R2:
			op.setColor(CRGB::Crimson);
			break;
		case R3:
			op.setColor(CRGB::Orange);
			break;
		case R4:
			op.setColor(CRGB::Yellow);
			break;
		case RUp:
			op.incrColor(CRGB::Red);
			break;
		case RDn:
			op.decrColor(CRGB::Red);
			break;
		case G:
			op.setColor(CRGB::Green);
			break;
		case G1:
			op.setColor(CRGB::LawnGreen);
			break;
		case G2:
			op.setColor(CRGB::DarkCyan);
			break;
		case G3:
			op.setColor(CRGB::Olive);
			break;
		case G4:
			op.setColor(CRGB::SeaGreen);
			break;
		case GUp:
			op.incrColor(CRGB::Green);
			break;
		case GDn:
			op.decrColor(CRGB::Green);
			break;
		case B:
			op.setColor(CRGB::Blue);
			break;
		case Blue1:
			op.setColor(CRGB::Aqua);
			break;
		case B2:
			op.setColor(CRGB::MidnightBlue);
			break;
		case B3:
			op.setColor(CRGB::DarkViolet);
			break;
		case B4:
			op.setColor(CRGB::Fuchsia);
			break;
		case BUp:
			op.incrColor(CRGB::Blue);
			break;
		case BDn:
			op.decrColor(CRGB::Blue);
			break;
		case W:
			op.setColor(CRGB::White);
			break;
		case W1:
			op.setColor(CRGB::Bisque);
			break;
		case W2:
			op.setColor(CRGB::Khaki);
			break;
		case W3:
			op.setColor(CRGB::LightBlue);
			break;
		case W4:
			op.setColor(CRGB::LightSlateGray);
			break;
		case Quick:
			break;
		case Slow:
			break;
		case Diy1:
			op.HSV();
			break;
		case Diy2:
			break;
		case Diy3:
			break;
		case Diy4:
			op.HSV(true);
			break;
		case Diy5:
			break;
		case Diy6:
			break;
		case Auto:
			break;
		case Flash:
			break;
		case Jump3:
			op.setAnimation(1);
			break;
		case Jump7:
			op.setAnimation(2);
			break;
		case Fade3:
			op.nextPalette();
			break;
		case Fade7:
			op.save();
			break;
		default:
			break;
		}
		irrecv.resume();
	}
	if (irrecv.isIdle()) {
		op.nextFrame();
		op.update();
	}

}

