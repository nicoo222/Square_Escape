#include "lib.h"


//gcc main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c -lSDL2 -lSDL2_mixer -o game
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
	
	fprintf(stderr,"Parce que c'est mieux avec un printf");
	
	// on donne une graine pour générer des nombres random
	srand(time());
	
	// Durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	screen.frameDuration = 17;
	
	//boucle principale
	while(!in.quit){
	
		if (gameState.menu) {
			updateInput(&in);
			updateMenu(&in,&gameState);
			updateScreenMenu(&menu,&screen,&gameState);
		}
		
		else {
		
			playLoop (&in,&gameState,&character,&enemies,&collision,&screen,&gameOptions);
			
			//Pour une raison une ou autre la partie en cours s'est arretée
			if(!in.quit){
				gameState.waiting=1;
				
				//On attend que l'utilisateur décide de rejouer ou non
				endGameLoop(&in,&gameState,&character,&enemies,&screen);
			}
		}
	}
	
	endGame(&screen);
	
	return EXIT_SUCCESS;
}
