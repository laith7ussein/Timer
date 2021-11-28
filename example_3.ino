/**
 * Like setIntreval, it repeats a specific callback with time but
 * with anothor factor ...
 * the repeatIn method is used to repeat a callback N times at every T time
 * in this example we are printing "Hello World!" 10 times every 1 second ...
 */

#include <Timer.h>

Timer timer;

void setup() {
	Serial.begin(9600);
}

void loop() {
	
	timer.repeatIn(10, 1000, [] () {
		Serial.println("Hello World!");
	});

}
