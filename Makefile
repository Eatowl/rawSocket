all:
	gcc -Wall -o server serverUDP.c -O2
	gcc -Wall -o client clientUDP.c -O2