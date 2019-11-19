ifdef ($(VAR))
	RUN = ./program (VAR)
else 
	RUN = ./program	
endif

all: main.o
	gcc -o program main.o

main.o: main.c
	gcc -c main.c

run:
	$(RUN)

clean:
	rm *.o
	rm *~