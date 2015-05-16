#include "gameFunctions.h"
#include "screenFunctions.h"

int main(int argc, char *argv[])
{
	Character character;
	Enemies enemies;
	GameState gameState;
	Screen screen;
	Input in;
	Collision collision;
	
	gameInitialization(&screen);
	audioInitilization();
	
	int frameTime, currentTime, frame = 0, delay;
	
	memset(&gameState,0,sizeof(gameState));
	memset(&in,0,sizeof(in));
	
	while(!in.quit){

		//Si le retour de boucle s'effectue dans le cas d'une nouvelle partie ou si le joueur a décidé de rejouer
		if(!gameState.pause){
			characterInitialization(&character,&screen);
			enemiesInitialization(&enemies,&screen);
			updateScreen(&character,&enemies,&screen);
		}
		
		//Mise à 0 des des booléens des structures.
		memset(&in,0,sizeof(in));
		memset(&gameState,0,sizeof(gameState));
		
		while(!gameState.pause && !in.quit && !gameState.lost){
		    frameTime = SDL_GetTicks();
		    frame++;
		    moveEnemies(&enemies);
		    updateInput(&in);
		    checkCollision(&character,&enemies,&collision,&gameState);
		    updateScreen(&character,&enemies,&screen);
		    
			if (in.keys[SDL_SCANCODE_UP]){
		 	  	if(!collision.up){
		  			character.squarePosition.y-=6;
			 	}
			}
		
			if (in.keys[SDL_SCANCODE_LEFT]){
				if(!collision.left){
			  		character.squarePosition.x-=6;
		  		}
			  		
			}

			if (in.keys[SDL_SCANCODE_DOWN]){
			  	if(!collision.down){
			  		character.squarePosition.y+=6;
		  		}
			}

			if(in.keys[SDL_SCANCODE_RIGHT]){
			  if(!collision.right){
			  		character.squarePosition.x+=6;
		  		}
			}
		
			if(in.keys[SDL_SCANCODE_P]){
				gameState.pause=1;
				in.keys[SDL_SCANCODE_P]=0;
			}
			
			if(in.keys[SDL_SCANCODE_SPACE]){
				enemies.numberOfEnemies++;
				in.keys[SDL_SCANCODE_SPACE]=0;
			}
			
			currentTime = SDL_GetTicks();
			
			delay = 4 - currentTime + frameTime;
			if (delay > 0) {
				SDL_Delay(4 - currentTime + frameTime);
			}
		}
		
		if(!in.quit){
			gameState.waiting=1;
			
			if(gameState.lost){
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
			else {
				while(gameState.waiting && !in.quit){
					updateInput(&in);
					
					if(in.keys[SDL_SCANCODE_P]){
						gameState.waiting=0;
					}
				}
			}
		}
    }
    
    
    
    endGame(&screen);    
                       
	return EXIT_SUCCESS;
}
