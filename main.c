#include "gameFunctions.h"
#include "screenFunctions.h"
#include "lib.h"
#include "gameLoop.h"
#include "gameStructures.h"

int main(int argc, char *argv[])
{
	Character character;
	Enemies enemies;
	GameState gameState;
	Screen screen;
	Collision collision;
	Input in;
	int frame;
	
	gameInitialization(&screen);
	audioInitilization();
	
	memset(&gameState,0,sizeof(gameState));
	memset(&in,0,sizeof(in));
	
	// on donne une draine pour générer des nombres random
	srand(time());

	
	// Durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	screen.frameDuration = 17;
	
	playLoop (&in,&gameState,&frame,&character,&enemies,&collision,&screen);
	

		
	//Pour une raison une ou autre la partie en cours s'est arretée
	if(!in.quit){
		gameState.waiting=1;
		//Pause
		if(gameState.pause){
			while(gameState.waiting && !in.quit){
				updateInput(&in);
				if(in.keys[SDL_SCANCODE_P]){
					gameState.waiting=0;
					in.keys[SDL_SCANCODE_P]=0;
				}
			}
		}
		//Fin de partie
		else {
			//On attend que l'utilisateur décide de rejouer ou non
			while(gameState.waiting && !in.quit){
				updateInput(&in);
			
				if(in.keys[SDL_SCANCODE_N]){
					in.quit=1;
					gameState.waiting=0;
				}
			
				if(in.keys[SDL_SCANCODE_Y]){
					gameState.waiting=0;
				}
			}
		}
	}
	endGame(&screen);   
                       
	return EXIT_SUCCESS;
}
