#include "gameFunctions.h"
#include "screenFunctions.h"
#include "lib.h"

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
	// durée de la boucle de jeu en ms
	// 17 correspond envirron à 60 fps
	int frameDuration = 17;
	
	memset(&gameState,0,sizeof(gameState));
	memset(&in,0,sizeof(in));
	
	srand(time());
	
	while(!in.quit){
		//Mise à 0 des des booléens des structures
		memset(&in,0,sizeof(in));
		memset(&gameState,0,sizeof(gameState));
		
		characterInitialization(&character,&screen);
		enemiesInitialization(&enemies,&screen);
		updateScreen(&character,&enemies,&screen);
		
		while(!in.keys[SDL_SCANCODE_P] && !in.quit && !gameState.lost){
			frameTime = SDL_GetTicks();
			frame++;
			printf("%d",rand()%5);
			//on ajoute un ennemy régulièrement
			if (frame%120 == 0){
				addOneEnemy(&enemies);
			}
			
			updateInput(&in);
			
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
			
			if(in.keys[SDL_SCANCODE_SPACE]){
				enemies.numberOfEnemies++;
				in.keys[SDL_SCANCODE_SPACE]=0;
			}
			
			
			checkCollision(&character,&enemies,&collision,&gameState);
			moveEnemies(&enemies);
			updateScreen(&character,&enemies,&screen);
			
			//code pour attendre un durée de frame fixe
			currentTime = SDL_GetTicks();
			delay = frameDuration - currentTime + frameTime;
			if (delay > 0) {
				SDL_Delay(frameDuration - currentTime + frameTime);
			}
		}
		
		if(!in.quit){
			gameState.waiting=1;
			
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
