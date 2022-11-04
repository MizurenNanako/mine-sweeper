CC			= gcc
CFLAGS  	= -O2
LDFLAGS    	= -lm

debug : CFLAGS = -g
debug : main

main : OBJS = main.o printer_cli.o
main : main.o printer_cli.o
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

(*.o) : $(*.c)
	$(CC) $(CFLAGS) -c $(*.c)

clean :
	rm *.o
