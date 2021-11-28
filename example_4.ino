/**
 * Like repeatIn method but this method while it's repeating the callback
 * it will map a value, starting from the giving minimum and at the end it
 * reach the maximum ...
 *
 * In this exaple we are repeating a callback 10 times each 1 second and geting
 * a value between 0-180 will increase in the loop, the repeation will be stoped
 * after the maximum value reached ...
 *
 * at first callback loop value = 0
 * ----------------- then value = value + (180-0)/10 = 18
 * ----------------- then value = value + (180-0)/10 = 36
 * ----------------- then value = value + (180-0)/10 = 50  ....  etc
 * the maximum value 180 will be reached within 1 second only and in
 * 10 steps of increasement...
 */

#include <Timer.h>

Timer timer;

void setup() {
	Serial.begin(9600);
}

void loop() {
	
	timer.reachIn(10, 1000, 0, 180, [] (double value) {
		Serial.println( value );
	});
  
//  USE AN OPTIONAL CALLBACK TO BE EXECUTED AFTER THE MAUMUM VALUE BE REACHED (see example_1)
//   timer.reachIn(10, 1000, 0, 180, [] (double value) {
// 		Serial.println( value );
// 	}, [] () {
//     Serial.print( "Hey, I im finished!" );
//   } );

}
