# Makefile de Square_Escape avec pour exécutable 'game'

Programme : main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c menu.c unit.c
	gcc main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c menu.c unit.c -lSDL2 -lSDL2_mixer -lSDL2_ttf -o game
