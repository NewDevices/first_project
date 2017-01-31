#include <RCSwitch.h>
#include <LiquidCrystal.h>

#define BASE_CODE1 5313876
#define BASE_CODE2 5326164
#define BIT_LENGTH 24
#define KEY_COUNT 5

const int keyLimits[] = {50, 190, 380, 555, 790, 1024};

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

/**
 * Return they key code that corresponds to a given value.
 *
 * KeyCode | Key
 * --------+-----------------------
 *       5 | no key
 *       4 | select
 *       3 | left
 *       2 | down
 *       1 | up
 *       0 | right
 *      -1 | Could not resolve key.
 */
int getKeyCode(int value) {
	for (int i = 0; i <= KEY_COUNT; i++) {
		if (value < keyLimits[i]) {
			return i;
		}
	}
	return -1;
}

void setup() {
	lcd.begin(16, 2);
	pinMode(A5, OUTPUT);
	rcSwitch.enableTransmit(A5);
	rcSwitch.setProtocol(1);
}

void loop() {
}
