CFLAGS = -Wall -ansi -pedantic

game_global: game_global.c
	gcc $(CFLAGS) game_global.c -o game_global

game_local: game_local.c
	gcc $(CFLAGS) game_local.c -o game_local

clean:
	rm -rf game_global game_local