/**
 * Repeat a specific action in a fixed time interval...
 * In this example: print "Hello World" every 1 second
 */

#include <Timer.h>

Timer timer;

void setup() {
	Serial.begin(9600);
}

void loop() {
	
	timer.setInterval(1000, [] () {
		Serial.println("Hello World!");
	});

}
