#include "gameLoop.h"


void playLoop (Input *pIn,GameState *pGameState,int *pFrame,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen){
	while(!pIn->quit){
		//Si la raison de la sortie de boucle était la fin de la partie
		if(!pGameState->pause){
			characterInitialization(pCharacter,pScreen);
			enemiesInitialization(pEnemies,pScreen);
			updateScreen(pCharacter,pEnemies,pScreen);
		}
		
		//Mise à 0 des des booléens des structures
		memset(pIn,0,sizeof(*pIn));
		memset(pGameState,0,sizeof(*pGameState));
		
		while(!pGameState->pause && !pIn->quit && !pGameState->lost){
			int frameTime = SDL_GetTicks();
			pFrame++;
			//on ajoute un ennemi régulièrement
			if (*pFrame%240 == 0){
				addOneEnemy(&pEnemies);
			}
			
			updateInput(pIn);
			
			if (pIn->keys[SDL_SCANCODE_UP]){
				if(!pCollision->up){
					pCharacter->squarePosition.y-=6;
				}
			}
		
			if (pIn->keys[SDL_SCANCODE_LEFT]){
				if(!pCollision->left){
					pCharacter->squarePosition.x-=6;
				}
					
			}

			if (pIn->keys[SDL_SCANCODE_DOWN]){
				if(!pCollision->down){
					pCharacter->squarePosition.y+=6;
				}
			}

			if(pIn->keys[SDL_SCANCODE_RIGHT]){
			  if(!pCollision->right){
					pCharacter->squarePosition.x+=6;
				}
			}
			
			if(pIn->keys[SDL_SCANCODE_P]){
			 	pGameState->pause=1; 		
				pIn->keys[SDL_SCANCODE_P]=0;
			}
			
			checkCollision(pCharacter,pEnemies,pCollision,pGameState);
			moveEnemies(pEnemies);
			updateScreen(pCharacter,pEnemies,pScreen);
			
			//Code pour attendre une durée de frame fixe
			int currentTime = SDL_GetTicks();
			int delay = pScreen->frameDuration - currentTime + frameTime;
			
			if (delay > 0) {
				SDL_Delay(delay);
			}
		}
	}
}


