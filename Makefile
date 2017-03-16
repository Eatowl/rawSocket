all:
	gcc -Wall -o server serverUDP.c -g
	gcc -Wall -o client clientUDP.c -g