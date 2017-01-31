#include <RCSwitch.h>
#include <LiquidCrystal.h>

#define BASE_CODE1 5313876
#define BASE_CODE2 5326164
#define BIT_LENGTH 24

LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7);
RCSwitch rcSwitch = RCSwitch();

/**
 * Get the RC code for a given receiver corresponding to whether you want to set
 * it to on or off.
 */
long getRcCode(int receiver, bool setOn) {
	long code = setOn ? 1 : 0;
	switch (receiver) {
		case 1: code += BASE_CODE1; break;
		case 2: code += BASE_CODE2; break;
	}
	return code;
}

void setup() {
	lcd.begin(16, 2);
	pinMode(A5, OUTPUT);
	rcSwitch.enableTransmit(A5);
	rcSwitch.setProtocol(1);
}

void loop() {
}
