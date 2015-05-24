#include "gameLoop.h"
#include "gameFunctions.h"

void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu,GameOptions* pGameOptions){
	updateMenu(pGameState,pMenu,pScreen);
	while(pGameState->menu && !pIn->quit){
		updateInput(pIn);
		//on teste quelle touche est appuyée
		if (pIn->keys[SDL_SCANCODE_DOWN]){
			if (!pGameState->choice){
				pGameState->choice ++;
				updateMenu(pGameState,pMenu,pScreen);
			}
		}
		if (pIn->keys[SDL_SCANCODE_UP]){
			if (pGameState->choice){
				pGameState->choice --;
				updateMenu(pGameState,pMenu,pScreen);
			}
		}
		if (pIn->keys[SDL_SCANCODE_RETURN]){
		  	pGameState->menu = 0;
			if (pGameState->choice == 1){
				pIn->quit = 1;
			}
		}
		if (pIn->keys[SDL_SCANCODE_E]){
		  	pGameOptions->mode = (pGameOptions->mode+1)%2;
		}
		SDL_RenderPresent(pScreen->renderer);
		SDL_Delay(15);
	}
}

void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager,GameOptions* pGameOptions){
	long frame = 0;
	long frameTime = 0;
	long delay = 0;
	
	enemiesInitialization(pEnemies,pScreen);
	pGameState->lost = 0;
	pTimeManager->debutTicks = (long) SDL_GetTicks();
	pTimeManager->playingTime=0;
	
	//On charge le BG du mode
	SDL_Surface* BGSurface;
	BGSurface = SDL_LoadBMP("Pictures/fond_space.bmp");
	if (BGSurface == NULL){
		fprintf(stderr,"Erreur chargement de l'image menuBG\n");
		exit(1);
	}
	pGameOptions->BG = SDL_CreateTextureFromSurface(pScreen->renderer,BGSurface);
	pGameOptions->BGRec.x = 0;
	pGameOptions->BGRec.y = 0;
	pGameOptions->BGRec.w = PLAYING_AREA_WIDTH;
	pGameOptions->BGRec.h = PLAYING_AREA_HEIGHT;

	while(!pGameState->menu && !pIn->quit && !pGameState->lost){
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
		//On met à jours l'afficheur du temps de jeu mais pas trop souvent
		if(frame%20 == 0){
			updateTTFManager(pScreen,pTTFManager,pTimeManager,pEnemies);
		}
		//On réaffiche l'ensemble
		SDL_RenderClear(pScreen->renderer);
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
		SDL_RenderPresent(pScreen->renderer);
		//Si on a appuyé sur p on rentre dans la boucle de pause
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=1; 		
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		if(pIn->keys[SDL_SCANCODE_Q]){
			pGameState->menu=1;
		}
		if(pGameState->pause){
			//il faut arrêter replacer le compteur de temps après la pause
			long pauseDebut = (long) SDL_GetTicks();
			pauseLoop(pGameState,pIn,pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
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
		endGameLoop(pIn,pGameState,pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
	}
	SDL_FreeSurface(BGSurface);
}

void pauseLoop(GameState* pGameState,Input* pIn,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions){
	//On met le compteur en pause
	updateScreen(pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
	SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL1, NULL, &pTTFManager->pauseTextL1Rec);
	SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL2, NULL, &pTTFManager->pauseTextL2Rec);
	SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL3, NULL, &pTTFManager->pauseTextL3Rec);
	while(pGameState->pause && !pIn->quit){
		updateInput(pIn);
		SDL_RenderPresent(pScreen->renderer);
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=0;
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		if(pIn->keys[SDL_SCANCODE_Q]){
			pGameState->pause=0;
			pGameState->menu=1;
		}
		SDL_Delay(15);
	}
}

void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions){
	while(pGameState->waiting && !pIn->quit){
	  	updateScreen(pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->playAgain, NULL, &pTTFManager->playAgainRec);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->BAM, NULL, &pTTFManager->BAMRec);
		SDL_RenderPresent(pScreen->renderer);
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

void mode1Loop(Input *pIn,GameOptions* pGameOptions,Screen* pScreen, GameState* pGameState){
	MusicManager musicManager;
	audioInitialization(&musicManager);
	
	TTFManager ttfManager;
	ttfInitialization(pScreen,&ttfManager);
	initPauseText(pScreen, &ttfManager);
	
	Character character;
	characterInitialization(&character,pScreen);
	
	Enemies enemies;
	enemiesInitialization(&enemies,pScreen);
	Unit seed;
	memset(&seed,0,sizeof(seed));
	
	
	
	Collision collision;
	
	TimeManager timeManager;
	timeManager.debutTicks = (long) SDL_GetTicks();
	timeManager.playingTime=0;

	long frame = 0;
	long frameTime = 0;
	long delay = 0;
	
	pGameState->lost = 0;
	//On charge le BG du mode
	SDL_Surface* BGSurface;
	BGSurface = SDL_LoadBMP("Pictures/fond_grass.bmp");
	if (BGSurface == NULL){
		fprintf(stderr,"Erreur chargement de l'image BGSurface\n");
		exit(1);
	}
	pGameOptions->BG = SDL_CreateTextureFromSurface(pScreen->renderer,BGSurface);
	pGameOptions->BGRec.x = 0;
	pGameOptions->BGRec.y = 0;
	pGameOptions->BGRec.w = PLAYING_AREA_WIDTH;
	pGameOptions->BGRec.h = PLAYING_AREA_HEIGHT;
	SDL_FreeSurface(BGSurface);
	updateTTFManager(pScreen,&ttfManager,&timeManager,&enemies);

	while(!pGameState->menu && !pIn->quit && !pGameState->lost){
		frameTime = (long) SDL_GetTicks();
		frame++;
		
		updateInput(pIn);
		checkCollision(&character,&enemies,&collision,pGameState);
		moveEnemies(&enemies);
		moveCharacter(pIn,&collision,&character);
		//On ajoute un ennemi régulièrement
		if (frame%240 == 0){
			addOneEnemy(&enemies);
		}
		//On met à jours l'afficheur du temps de jeu mais pas trop souvent
		if(frame%20 == 0){
		      updateTTFManager(pScreen,&ttfManager,&timeManager,&enemies);
		}
		//On affiche l'ensemble
		SDL_RenderClear(pScreen->renderer);
		updateScreen(&character,&enemies,pScreen,&ttfManager,pGameOptions);
		SDL_RenderPresent(pScreen->renderer);
		//Si on vérifie si le joueur veux mettre en pause(P) ou quitter (Q)
		if(pIn->keys[SDL_SCANCODE_P]){
			pGameState->pause=1;
			pIn->keys[SDL_SCANCODE_P]=0;
		}
		if(pIn->keys[SDL_SCANCODE_Q]){
			pGameState->menu=1;
		}
		
		//boucle de pause
		if(pGameState->pause){
			//il faut arrêter replacer le compteur de temps après la pause
			long pauseDebut = (long) SDL_GetTicks();
			pauseLoop(pGameState,pIn,&character,&enemies,pScreen,&ttfManager,pGameOptions);
			timeManager.debutTicks += (long) SDL_GetTicks() - pauseDebut;
		}
		
		//Code pour attendre une durée de frame fixe
		delay = pScreen->frameDuration - (long) SDL_GetTicks() + frameTime;
		if (delay > 0) {
			SDL_Delay(delay);
		}
	}
	
	//Si le joueur sort du jeu car il a perdu la partie courante
	if(pGameState->lost){
		pGameState->waiting=1;
		
		//Petit son de défaite 
		Mix_PauseMusic(); 
		Mix_PlayChannel(1, musicManager.sound[0], 0);
		
		//On attend que l'utilisateur décide de rejouer ou non
		endGameLoop(pIn,pGameState,&character,&enemies,pScreen,&ttfManager,pGameOptions);
	}
}



