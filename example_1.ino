/**
 * Control twp servo motors, 
 * 1- first one start from 0 to 180 within 10 seconds
 * 2- first one stops and second one start from 0 to 180 within 5 seconds
 * 3- second one stops and the first one back to 0 within 10 seconds
 * 4- first one stops and the seconds one back to 0 too but within 5 seconds
 * 5- repeat ...
 */

#include <Servo.h>
#include <Timer.h>

Servo s1;
Servo s2;

Timer timer1;
Timer timer2;
Timer timer3;
Timer timer4;

void setup() {
	Serial.begin(9600);
  	s1.attach(8);
  	s2.attach(9);
	s1.write(0);
	s2.write(0);
}

void loop() {
	
	// servo 1 ==> 0-180 within 10000ms
	timer1.reachIn(360, 10000, 0, 180, [] (double value) -> void {
		s1.write(value);

	}, [] () -> void { // servo 1 reached 180
		
		// servo 2 ===> 0-180
		timer2.reachIn(360, 5000, 0, 180, [] (double value) -> void {
			s2.write(value);

		}, [] () -> void { // servo 2 reached 180
			
			// servo 1 ===> 180-0
			timer3.reachIn(360, 10000, 180, 0, [] (double value) -> void {
				s1.write(value);

			}, [] () -> void { // servo 1 reached 0
				
				// servo 2 ===> 180-0
				timer4.reachIn(360, 5000, 180, 0, [] (double value) -> void {
					s2.write(value);

				}, [] () -> void { // servo 2 reached 0
					
					// reset all timers and back to timer 1
					Serial.println("Full cicle completed");
					timer1.reset();
					timer2.reset();
					timer3.reset();
					timer4.reset();

				});

			});

		});

	});

}
