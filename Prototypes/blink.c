#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void menu();
void loadingPhase();
void transPhase();
void dispensePhase();
int off(int time);
int on(int time);


int transac = 1;
int selection = 1;

int main (int argc, char* argv[]) {
	
	if (wiringPiSetup() == -1) {
        printf ("Setup wiringPi Failed!\n");
    }
    pinMode(0, OUTPUT); 
	pinMode(2, OUTPUT); 
	pinMode(3, OUTPUT); 
	off(0);
	
	//while(selection)
		menu();
		
}

void menu() {
	char input;
	
	while (selection) {
		if(input != '\n')
			fputs("Enter l for loading, t for transaction, or q to quit\n", stdout);
		input = getchar();
		if (input == 'l') {
			loadingPhase();
			off(0);
		}
		if (input == 't') {
			transPhase();
			off(0);
		}
		if (input == 'q') {
			off(0);
			selection = 0;
		}
	}
}

// loading phase all LED turn on
void loadingPhase() {
	on(0);
	delay (3000);
	off(0);
}

// transaction phase, when push button: 
//if morning, turn on LED 0
//if afternoon, turn on LED 2
//if evening, turn on LED 3
void transPhase() {
	
	char input;
	
	while(transac) {
		if (input != '\n')
			fputs("Enter a character based on the time of day: m, a, n. Or q to quit\n", stdout);
		input = getchar();
		if (input == 'm') {
			off(0);
			dispensePhase();
		}
		if (input == 'a') {
			off(0);
			dispensePhase();
		}	
		if (input == 'n') {
			off(0);
			dispensePhase();
		}
		if (input == 'q') {
			off(0);
			transac = 0;
		}
	}
}

// dispensing phase, button push 3 times, LED blink
void dispensePhase() {
	char input[10];
	
	fputs("Please type 123 to indicate you are still present.\n", stdout);
	scanf("%s", input);
	
	if (!strcmp(input, "123")) {
		off(0);
		on(0);
		delay(300);
		off(0);
		delay(100);
		on(0);
		delay(300);
		off(0);
		delay(100);
		on(0);
		delay(300);
		off(0);		
	}
	else
		printf("wrong input\n");
}

int off(int time) {
	delay(time);
	digitalWrite(0, LOW);
	digitalWrite(2, LOW);
	digitalWrite(3, LOW); 
	return 0;
}

int on(int time) {
	delay(time);
	digitalWrite(0, HIGH);
	digitalWrite(2, HIGH);
	digitalWrite(3, HIGH); 
	return 0;
}


