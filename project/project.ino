#include <RCSwitch.h>
#include <LiquidCrystal.h>
#include <Servo.h>

/**
 * @author: Hendrik Werner // s4549775
 * @author: Timo Schrijvers // s4596331
 */

#define MIN_ANGLE 30
#define MAX_ANGLE 170
#define SERVO_STEP 10

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

/**
 * Print the status of the switches to the lcd.
 */
void printStatus(bool setOn1, bool setOn2) {
	lcd.setCursor(0, 0);
	lcd.print("Status 1: ");
	lcd.print(setOn1 ? "on " : "off");
	lcd.setCursor(0, 1);
	lcd.print("Status 2: ");
	lcd.print(setOn2 ? "on " : "off");
}

/**
 * Update the position of the servo. Repeatedly calling this will sway the servo
 * back and forth from MIN_ANGLE..MAX_ANGLE.
 */
void updateServoPos() {
	static int servoPos = MIN_ANGLE;
	static bool increaseServoPos = true;

	if (increaseServoPos) {
		servoPos += SERVO_STEP;
		if (servoPos >= MAX_ANGLE) {
			increaseServoPos = false;
		}
	} else {
		servoPos -= SERVO_STEP;
		if (servoPos <= MIN_ANGLE) {
			increaseServoPos = true;
		}
	}
	servo.write(servoPos);
}

void setup() {
	lcd.begin(16, 2);
	pinMode(A5, OUTPUT);
	rcSwitch.enableTransmit(A5);
	rcSwitch.setProtocol(1);
	printStatus(false, false);
}

void loop() {
	static bool setOn1 = false;
	static bool setOn2 = false;

	switch (getKeyCode(analogRead(A0))) {
		case 0: // right
			setOn1 = false;
			setOn2 = true;
			printStatus(setOn1, setOn2);
			break;
		case 1: // up
			setOn1 = true;
			setOn2 = true;
			printStatus(setOn1, setOn2);
			break;
		case 2: // down
			setOn1 = false;
			setOn2 = false;
			printStatus(setOn1, setOn2);
			break;
		case 3: // left
			setOn1 = true;
			setOn2 = false;
			printStatus(setOn1, setOn2);
			break;
	}
	rcSwitch.send(getRcCode(1, setOn1), BIT_LENGTH);
	rcSwitch.send(getRcCode(2, setOn2), BIT_LENGTH);
}
