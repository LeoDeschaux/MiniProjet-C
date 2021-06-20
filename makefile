GCC=gcc
SOURCES=$(wildcard *.c)
BINAIRES=$(patsubst %.c,%.o,${SOURCES})

all: 
	
main: ${BINAIRES}
	${GCC} $^ -o $@ -lm
	
%.o: %.c %.h
	${GCC} -c $<  

clean: 
	rm main
	rm *.o
