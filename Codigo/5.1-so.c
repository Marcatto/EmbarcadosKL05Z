#include "io.h"

#define SCK  5
#define Si  6
#define RCK  0
 

void shift_Init(void) {
	PinMode(SI,OUTPUT);
	PinMode(SCK,OUTPUT);
	PinMode(RCK,OUTPUT);

}

void shift_out(int value) {
	int x;
	digitalWrite(clockpin, LOW);
	digitalWrite(latchpin, LOW);
	for (x = 0; x < 8; x++) {
		if (value & 0x80) {
			digitalWrite(datapin, HIGH);
} else {
			digitalWrite(datapin, LOW);
}
		digitalWrite(clockpin, HIGH);
		digitalWrite(clockpin, LOW);
		value = (value << 1);
}
	digitalWrite(latchpin, HIGH);
	digitalWrite(latchpin, LOW);
}

