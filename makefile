CC			= gcc
CFLAGS  	= -O2
LDFLAGS    	= -lm -lcurses
OBJS		= main.o printer_cli.o input.o

debug : CFLAGS = -g
debug : main

main : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

(*.o) : $(*.c)
	$(CC) $(CFLAGS) -c $(*.c)

clean :
	rm *.o
	rm main
