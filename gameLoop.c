#include "gameLoop.h"


void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen, GameOptions *pGameOptions,MusicManager *pMusicManager,TTFManager *pTTFManager){

	characterInitialization(pCharacter,pScreen);
	enemiesInitialization(pEnemies,pScreen);
	updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
	pGameState->lost=0;
	
	if (pGameOptions->mode == 0){
		mode0Loop(pIn,pGameState,pCharacter,pEnemies,pScreen,pCollision,pMusicManager,pTTFManager);
	}
}

void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager){
	while(pGameState->waiting && !pIn->quit){
		updateInput(pIn);
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
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
		SDL_Delay(15);
	}
}

void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager){
	int frame = 0;
	long debut = (long) SDL_GetTicks()/1000;
	
	while(!pGameState->pause && !pIn->quit && !pGameState->lost){
		int frameTime = SDL_GetTicks();
		frame++;
		updateTTFManager(pScreen,pTTFManager, &debut);
		//on ajoute un ennemi régulièrement
		if (frame%240 == 0){
			addOneEnemy(pEnemies);
		}
		updateInput(pIn);
		moveCharacter(pIn,pCollision,pCharacter);
		
		//Pause
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=1; 		
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		if(pGameState->pause){	
			pauseLoop(pGameState,pIn,pCharacter,pEnemies,pScreen);
		}
		
		//affichage
		checkCollision(pCharacter,pEnemies,pCollision,pGameState);
		moveEnemies(pEnemies);
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
		
		//Code pour attendre une durée de frame fixe
		int currentTime = SDL_GetTicks();
		int delay = pScreen->frameDuration - currentTime + frameTime;
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
	//Pour une raison une ou autre la partie en cours s'est arretée
	if(pGameState->lost){
	
		pGameState->waiting=1;
		
		//Petit son de défaite 
		Mix_PauseMusic(); 
		Mix_PlayChannel(1, pMusicManager->sound[0], 0);
		
		//On attend que l'utilisateur décide de rejouer ou non
		endGameLoop(pIn,pGameState,pCharacter,pEnemies,pScreen,pTTFManager);
	}
}

void pauseLoop (GameState* pGameState,Input* pIn,Character *pCharacter,Enemies *pEnemies,Screen *pScreen){

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


