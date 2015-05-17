#include "lib.h"


//gcc main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c -lSDL2 -lSDL2_mixer -o game
int main(int argc, char *argv[]){
	Character character;
	Enemies enemies;
	GameState gameState;
	GameOptions gameOptions;
	Screen screen;
	Collision collision;
	Input in;
	
	audioInitilization();
	gameInitialization(&screen,&gameState,&in,&gameOptions);
	
	// on donne une graine pour générer des nombres random
	srand(time());
	
	// Durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	screen.frameDuration = 17;
	
	//boucle principale
	while(!in.quit){
		playLoop (&in,&gameState,&character,&enemies,&collision,&screen,&gameOptions);
			
		//Pour une raison une ou autre la partie en cours s'est arretée
		if(!in.quit){
			gameState.waiting=1;
			//On attend que l'utilisateur décide de rejouer ou non
			endGameLoop(&in,&gameState,&character,&enemies,&screen);
		}
	}
	endGame(&screen);
	
	return EXIT_SUCCESS;
}
