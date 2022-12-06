#include "pill_dispenser.h"

int transac = 1;
int selection = 1;
char input = '\0';

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int menu() {
	while (selection) {
		if (pthread_mutex_lock(&mutex))
			return EXIT_FAILURE;
		else
		{
			if(input != '\n')
				fputs("Enter l for loading, t for transaction, or q to quit\n", stdout);
			input = getchar();
			if (input == 'q') {
				fputs("QUITTING PROGRAM\N", stdout);
				selection = 0;
			}
			if (pthread_mutex_unlock(&mutex))
				return EXIT_FAILURE;
		}
	}
}

// loading phase all LED turn on
void* loadingPhase(void* void_pointer)
{
	while (1)
	{
		if (pthread_mutex_lock(&mutex))
			return NULL;
		else
		{
			if (input == 'l')
			{
				fputs("Loading phase: turn on all lights for 3 seconds\n", stdout);
			} 
			else if (input == 'q')
				return NULL;
			
			if (pthread_mutex_unlock(&mutex))
				return NULL;
		}
	}
}

// transaction phase, when push button: 
//if morning, turn on LED 0
//if afternoon, turn on LED 2
//if evening, turn on LED 3
void* transPhase(void* void_pointer) {	
	while (1) 
	{
		while(transac)
		{
			if (pthread_mutex_lock(&mutex))
				return NULL;
			else
			{
				if (input == 't')
				{
					if (input != '\n')
						fputs("Enter a character based on the time of day: m, a, n. Or q to quit\n", stdout);
					input = getchar();
					if (input == 'q') {
						fputs("QUITTING PROGRAM\n", stdout);
						transac = 0;
					}
				}
				if (pthread_mutex_unlock(&mutex))
					return NULL;
			}
		}
	}
}

// dispensing phase, button push 3 times, LED blink
void* dispensePhase(void* void_pointer) {
	char existence_check[10];
	while (1)
	{
		if (pthread_mutex_lock(&mutex))
			return NULL;
		else
		{
			if (input == 'm' || input == 'a' || input == 'n')
			{
				fputs("Please type 123 to indicate you are still present.\n", stdout);
				scanf("%s", existence_check);
				if (!strcmp(existence_check, "123"))
				{
					fputs("User verified, LEDs blink\n", stdout);
				}
				else
					fputs("Wrong input\n", stderr);
			}
			else if (input == 'q')
				return NULL;
			if (pthread_mutex_unlock(&mutex))
				return EXIT_FAILURE;
		}
	}
}

void print_scheduler(pid_t pid)
{
    switch (sched_getscheduler(pid))
    {
        case SCHED_FIFO:
            fputs("Pthread Policy is SCHED_FIFO\n", stdout);
            break;
        case SCHED_OTHER:
            fputs("Pthread Policy is SCHED_OTHER\n", stdout);
            break;
        case SCHED_RR:
            fputs("Pthread Policy is SCHED_RR\n", stdout);
            break;
        default: 
            fputs("Pthread Policy is UNKNOWN\n", stdout);
    }
}


