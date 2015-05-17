#include "gameFunctions.h"
#include "screenFunctions.h"
#include "gameLoop.h"

int main(int argc, char *argv[]){
	Character character;
	Enemies enemies;
	GameState gameState;
	Screen screen;
	Collision collision;
	Input in;
	
	audioInitilization();
	gameInitialization(&screen,&gameState,&in);
	
	// on donne une draine pour générer des nombres random
	srand(time());

	
	// Durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	screen.frameDuration = 17;
	
	while(!in.quit){
		
		playLoop (&in,&gameState,&character,&enemies,&collision,&screen);

			
		//Pour une raison une ou autre la partie en cours s'est arretée
		if(!in.quit){
			gameState.waiting=1;
			//On attend que l'utilisateur décide de rejouer ou non
			endGameLoop(&in,&gameState);
		}
	}
	endGame(&screen);   
                       
	return EXIT_SUCCESS;
}
