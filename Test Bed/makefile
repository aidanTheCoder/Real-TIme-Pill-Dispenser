INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS= 
CFLAGS= -O3 -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= -lpthread -lrt -Wall

PRODUCT=pill_dispenser

HFILES= pill_dispenser.h
CFILES= pill_dispenser_test_exec.c pill_dispenser.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

attitude_calculator:	attitude.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ pill_dispenser.o $(LIBS)

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
