build: main.c planificator.c planificator.h destroy.h
	gcc -Wall main.c planificator.c planificator.h destroy.h -o tema2
clean:
	rm -f tema2
