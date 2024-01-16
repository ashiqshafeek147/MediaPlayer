all:
	gcc -pthread player.c track.c main.c threadcntrl.c -l cjson -o app
	./app