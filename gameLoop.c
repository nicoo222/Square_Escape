#include "gameLoop.h"


void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen, GameOptions *pGameOptions,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager){
	characterInitialization(pCharacter,pScreen);
	enemiesInitialization(pEnemies,pScreen);
	updateTTFManager(pScreen,pTTFManager,pTimeManager,pEnemies);
	updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
	refreshScren(pScreen);
	
	if (pGameOptions->mode == 0){
		mode0Loop(pIn,pGameState,pCharacter,pEnemies,pScreen,pCollision,pMusicManager,pTTFManager,pTimeManager);
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

void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager){
	long frame = 0;
	long frameTime = 0;
	long delay = 0;
	
	pGameState->lost = 0;
	pTimeManager->debutTicks = (long) SDL_GetTicks();
	pTimeManager->playingTime=0;
	
	while(!pGameState->pause && !pIn->quit && !pGameState->lost){
		frameTime = (long) SDL_GetTicks();
		frame++;
		
		//On ajoute un ennemi régulièrement
		if (frame%240 == 0){
			addOneEnemy(pEnemies);
		}
		//On vérifie les collisions 
		checkCollision(pCharacter,pEnemies,pCollision,pGameState);
		//On met à jour les entrées claviers
		updateInput(pIn);
		//On déplace les objets du jeu
		moveEnemies(pEnemies);
		moveCharacter(pIn,pCollision,pCharacter);
		//On met à jours l'affichage du temps de jeu
		updateTTFManager(pScreen,pTTFManager,pTimeManager,pEnemies);
		//On réaffiche l'ensemble
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
		refreshScren(pScreen);
		//Si on a appuyé sur p on rentre dans la boucle de pause
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=1; 		
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		if(pGameState->pause){
			//il faut arrêter replacer le compteur de temps après la pause
			long pauseDebut = (long) SDL_GetTicks();
			pauseLoop(pGameState,pIn,pCharacter,pEnemies,pScreen,pTTFManager);
			pTimeManager->debutTicks += (long) SDL_GetTicks() - pauseDebut;
		}
		
		//Code pour attendre une durée de frame fixe
		delay = pScreen->frameDuration - (long) SDL_GetTicks() + frameTime;
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
	
	//Le joueur a perdu la partie courante
	if(pGameState->lost){
		pGameState->waiting=1;
		
		//Petit son de défaite 
		Mix_PauseMusic(); 
		Mix_PlayChannel(1, pMusicManager->sound[0], 0);
		
		//On attend que l'utilisateur décide de rejouer ou non
		endGameLoop(pIn,pGameState,pCharacter,pEnemies,pScreen,pTTFManager);
	}
}

void pauseLoop(GameState* pGameState,Input* pIn,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager){
	//On met le compteur en pause
	while(pGameState->pause && !pIn->quit){
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
		refreshScren(pScreen);
		updateInput(pIn);
		
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=0;
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		SDL_Delay(15);
	}
}

void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager){
	while(pGameState->waiting && !pIn->quit){
	  	updateScreen(pCharacter,pEnemies,pScreen,pTTFManager);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->playAgain, NULL, &pTTFManager->playAgainRec);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->BAM, NULL, &pTTFManager->BAMRec);
		refreshScren(pScreen);
		updateInput(pIn);
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



