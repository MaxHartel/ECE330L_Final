#include <stdio.h>
#include <seg7.h>
#include <math.h>
/*
* Final Lab
* April Clark & Max Hartel
* 4/22/22
*/
// Define registers for port D
#define gpiod_moder (*((volatile unsigned int*)0x40020c00))
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))
// Define registers for port C
#define gpioc_moder (*((volatile unsigned int*)0x40020800))
#define gpioc_idr (*((volatile unsigned int*)0x40020810))
#define gpioc_odr (*((volatile unsigned int*)0x40020814))

int main(){

	char hexArr[16] = {0x40,0x79,0x24,0x30,0x19,0x12,0x2,0x78,0x0,0x18,0x8,0x3,0x46,0x21,0x6,0xe}; //array storing hex values 0-15
	unsigned int switches, display_number, totalSeconds, minutes, seconds, totalMiliseconds;
	gpioc_moder = 0x00000000; // Port C mode register - make all pins inputs
	seg7_init(); // Initialize the 7-segment display



	while(1){

		//Switch 15 controls whether it is in run mode or reset mode
		if (!(switches & 0x00008000)){
			unsigned int sigSwitches = switches & 0x000f; //only taks input from the switches[0:3]

			// If SW15 is off, display '0' on seven seg displays 4:7
			for(display_number = 4; display_number < 8; display_number++){
				seg7_put(display_number, hexArr[0]); 
			}
			
			//turns off seg7 displays 0:3
			for(display_number = 0; display_number < 4; display_number++){
				seg7_put(display_number, 0xff); 
			}

			gpiod_odr = 0000000000000000; // turns off all leds

			totalSeconds = 0; //resets total seconds
		}else{

			int correct = 0;
			int secondsOnes;
			int secondsTens;
			int minutesOnes;
			int minutesTens;

			//counts total seconds and keeps track of time passed
			if(!correct){
				totalMiliseconds++;
				minutes = totalSeconds / 60;
				seconds = totalSeconds % 60;

				if(totalMiliseconds % 1000 == 0){
					totalSeconds++;
				}

				secondsOnes = seconds % 10; // gets the ones digit for seconds passed
				secondsTens = floor(seconds / 10);
				secondsTens = secondsTens % 10; // gets the tens digit for seconds passed

				minutesOnes = minutes % 10; // gets the ones digit for minutes passed
				minutesTens = floor(minutes / 10);
				minutesTens = minutesTens % 10; // gets the tens digit for minutes passed

				seg7_put(4, hexArr[secondsOnes]); //displays the ones digit for seconds on seg7 #4
				seg7_put(5, hexArr[secondsTens]); //displays the tens digit for seconds on seg7 #5
				seg7_put(6, hexArr[minutesOnes]); //displays the ones digit for tens on seg7 #6
				seg7_put(7, hexArr[minutesTens]); //displays the tens digit for seconds on seg7 #7

				delay_ms(1);


			}else{

				seg7_put(4, hexArr[secondsOnes]); //displays the ones digit for seconds on seg7 #4
				seg7_put(5, hexArr[secondsTens]); //displays the tens digit for seconds on seg7 #5
				seg7_put(6, hexArr[minutesOnes]); //displays the ones digit for tens on seg7 #6
				seg7_put(7, hexArr[minutesTens]); //displays the tens digit for seconds on seg7 #7

				int rand = rand() % 16;
			}
















		}

	}

	return 0;
}