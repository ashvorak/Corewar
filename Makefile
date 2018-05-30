all: 
	gcc -lncurses ./src/visual.c ./src/main.c ./src/read_players.c ./src/read_player.c libft.a -o visual