#include "gameLoop.h"


void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen, GameOptions *pGameOptions,MusicManager *pMusicManager){

	//Si la raison de la sortie de boucle était la fin de la partie

	characterInitialization(pCharacter,pScreen);
	enemiesInitialization(pEnemies,pScreen);
	updateScreen(pCharacter,pEnemies,pScreen);
	int frame;
	pGameState->lost=0;
	
	if (pGameOptions->mode == 0){
		while(!pGameState->pause && !pIn->quit && !pGameState->lost){
			int frameTime = SDL_GetTicks();
			frame++;
			//on ajoute un ennemi régulièrement
			if (frame%240 == 0){
				addOneEnemy(pEnemies);
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
			
			//Pause
			if(pGameState->pause){
				while(pGameState->pause && !pIn->quit){
					updateScreen(pCharacter,pEnemies,pScreen);
					updateInput(pIn);
					if(pIn->keys[SDL_SCANCODE_P]){
						pGameState->pause=0;
						pIn->keys[SDL_SCANCODE_P]=0;
					}
					SDL_Delay(15);
				}
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
			//Pour une raison une ou autre la partie en cours s'est arretée
		}
		
		if(pGameState->lost){
			pGameState->waiting=1;
			
			//Petit son de défaite en stoppant la musique en cours
			Mix_PauseMusic();
			Mix_PlayChannel(1, pMusicManager->sound[0], 0);

			//On attend que l'utilisateur décide de rejouer ou non
			endGameLoop(pIn,pGameState,pCharacter,pEnemies,pScreen);
		}
	}
}

void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen){
	while(pGameState->waiting && !pIn->quit){
		updateInput(pIn);
		updateScreen(pCharacter,pEnemies,pScreen);
		if(pIn->keys[SDL_SCANCODE_N]){
			pGameState->menu=1;
			pGameState->waiting=0;
		}
		
		if(pIn->keys[SDL_SCANCODE_Y]){
			pGameState->waiting=0;
		}
		SDL_Delay(15);
	}
}

void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu){
        while(pGameState->menu && !pIn->quit){
		updateInput(pIn);
		updateMenu(pIn,pGameState);
		updateScreenMenu(pMenu,pScreen,pGameState);
	}
}


