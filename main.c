#include "lib.h"


//gcc main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c menu.c -lSDL2 -lSDL2_mixer -o game
int main(int argc, char *argv[]){
	//Création des structures de jeu
	Character character;
	Enemies enemies;
	GameState gameState;
	GameOptions gameOptions;
	Screen screen;
	Collision collision;
	Input in;
	Menu menu;
	
	audioInitilization();
	gameInitialization(&screen,&gameState,&in,&gameOptions);
	
	loadMenu(&menu, &screen);
	updateScreenMenu(&menu,&screen,&gameState);
	
	gameState.menu = 1;
	
	//fprintf(stderr,"Parce que c'est mieux avec un printf"); // NON MAIS WTF SERIEUX ??!
	
	// on donne une graine pour générer des nombres random
	srand(time());
	
	// Durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	screen.frameDuration = 17;
	
	//Mise à 0 des des booléens des structures
	memset(&in,0,sizeof(in));
	memset(&gameState,0,sizeof(gameState));
	
	//boucle principale
	while(!in.quit){	
		menuLoop (&in, &gameState, &screen, &menu);
		playLoop (&in,&gameState,&character,&enemies,&collision,&screen,&gameOptions);
	}
	endGame(&screen);
	
	return EXIT_SUCCESS;
}
