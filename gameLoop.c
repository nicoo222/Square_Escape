#include "gameLoop.h"
#include "gameFunctions.h"

void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu,GameOptions* pGameOptions){
	updateScreenMenu(pMenu,pScreen,pGameState,pGameOptions);
	int flagE = 1;
	int flagUP = 1;
	int flagDOWN = 1;
	while(pGameState->menu && !pIn->quit){
		updateScreenMenu(pMenu,pScreen,pGameState,pGameOptions);
		updateInput(pIn);
		//on teste quelle touche est appuyée
		if (pIn->keys[SDL_SCANCODE_E]){
			if(!flagE){
				pGameOptions->mode = (pGameOptions->mode+1)%2;
				flagE = 1;
			}
		}else{
			flagE = 0;
		}
		if (pIn->keys[SDL_SCANCODE_DOWN]){
			if (!flagDOWN){
				if (pGameState->choice < 2){
					pGameState->choice ++;
					flagDOWN = 1;
				}
			}
		}else{
			flagDOWN = 0;
		}
	
		if (pIn->keys[SDL_SCANCODE_UP]){
			if (!flagUP){
				if (pGameState->choice > 0 ){
					pGameState->choice --;
					flagUP = 1;
				}
			}
		}else{
			flagUP = 0;
		}
		
		if (pIn->keys[SDL_SCANCODE_RETURN]){		
			if (pGameState->choice == 0){
				pGameState->menu = 0;
			}
			if (pGameState->choice == 1){
				pGameState->menu = 2;
				menuOptionLoop (pIn,pGameState,pScreen,pMenu,pGameOptions);
				pGameState->choice = 1;
				pGameState->menu = 1;
			}
			if (pGameState->choice == 2){
				pIn->quit = 1;
			}
		}
		SDL_Delay(15);
	}
}

void menuOptionLoop (Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu,GameOptions* pGameOptions){
	if(pGameOptions){
	  // ça enlèbe un warning
	}
	int goOut = 0;
	int flagUP = 1;
	int flagDOWN = 1;
	int flagRETURN = 1;
	pGameState->choice = 0;
	while(!goOut && !pIn->quit){
	  	updateInput(pIn);
		if (pIn->keys[SDL_SCANCODE_DOWN]){
			if (!flagDOWN){
				if (pGameState->choice < 1){
					pGameState->choice ++;
					flagDOWN = 1;
				}
			}
		}else{
			flagDOWN = 0;
		}
		
		if (pIn->keys[SDL_SCANCODE_UP]){
			if (!flagUP){
				if (pGameState->choice > 0 ){
					pGameState->choice --;
					flagUP = 1;
				}
			}
		}else{
			flagUP = 0;
		}
		
		if (pIn->keys[SDL_SCANCODE_RETURN]){
			if(!flagRETURN){
				if (pGameState->choice == 0){
					flagRETURN = 1;
					pGameState->sChoice = (pGameState->sChoice+1)%2;
					if (pGameState->sChoice == 0){
						Mix_VolumeMusic(0);
					} else {
						Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
					}
				}
				if (pGameState->choice == 1){
					pGameOptions->BGChoice = (pGameOptions->BGChoice + 1)%2;
					pGameOptions->BG = pMenu->BgChoice[pGameOptions->BGChoice];
					flagRETURN = 1;
				}
			}
		}else{
			flagRETURN = 0;
		}
		
		if (pIn->keys[SDL_SCANCODE_BACKSPACE]){	
			goOut = 1;
		}
		updateScreenMenu(pMenu,pScreen,pGameState,pGameOptions);
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
	
	Mix_PlayMusic(pMusicManager->music[pMusicManager->currentMusic], -1); //Jouer infiniment la musique
	
	//On set la taille du BG du mode
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
			//on print dans le renderer ce qu'on veut afficher pendant la pause
			updateScreen(pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
			SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL1, NULL, &pTTFManager->pauseTextL1Rec);
			SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL2, NULL, &pTTFManager->pauseTextL2Rec);
			SDL_RenderCopy(pScreen->renderer, pTTFManager->pauseTextL3, NULL, &pTTFManager->pauseTextL3Rec);
			pauseLoop(pGameState,pIn,pScreen);
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
		//Petit son de défaite et on stoppe la musique courante 
		Mix_PauseMusic(); 		
		Mix_PlayChannel(1, pMusicManager->sound[0], 0);
		
		if(pMusicManager->currentMusic==0){
			pMusicManager->currentMusic=1;
		}
		else pMusicManager->currentMusic=0;
		
		//On print l'affichage de fin de partie
		updateScreen(pCharacter,pEnemies,pScreen,pTTFManager,pGameOptions);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->playAgain, NULL, &pTTFManager->playAgainRec);
		SDL_RenderCopy(pScreen->renderer, pTTFManager->BAM, NULL, &pTTFManager->BAMRec);
		//On attend que l'utilisateur décide de rejouer ou non
		endGameLoop(pIn,pGameState,pScreen);
		
	}
}

void pauseLoop(GameState* pGameState,Input* pIn,Screen *pScreen){
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

void endGameLoop(Input *pIn,GameState *pGameState,Screen *pScreen){
	while(pGameState->waiting && !pIn->quit){
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
	Mix_PlayMusic(musicManager.music[musicManager.currentMusic], -1); //Jouer infiniment la musique
	
	TTFManager ttfManager;
	ttfInitialization(pScreen,&ttfManager);
	initPauseText(pScreen, &ttfManager);
	
	Character character;
	characterInitialization(&character,pScreen);
	
	Enemies enemies;
	enemiesInitialization(&enemies,pScreen);
	Unit seed;
	initSeed(&seed,pScreen);
	randomMove(&seed);
	
	Collision collision;
	
	TimeManager timeManager;
	timeManager.debutTicks = (long) SDL_GetTicks();
	timeManager.playingTime=0;

	long frame = 0;
	long frameTime = 0;
	long delay = 0;
	int score = 0;
	Texte scoreTexte = {0};
	scoreTexte.rec.x=865;
	scoreTexte.rec.y=580;
	scoreTexte.rec.w=0;
	scoreTexte.rec.h=30;
	
	
	pGameState->lost = 0;
	//On set la taille du BG du mode
	pGameOptions->BGRec.x = 0;
	pGameOptions->BGRec.y = 0;
	pGameOptions->BGRec.w = PLAYING_AREA_WIDTH;
	pGameOptions->BGRec.h = PLAYING_AREA_HEIGHT;
	updateTTFManager(pScreen,&ttfManager,&timeManager,&enemies);
	updateSeedScore(pScreen, &scoreTexte, score, &ttfManager);

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
		//Est ce que le joueur à trouver une seed ?
		if(checkUnitCollisionWIthCharacter(&seed, &character)){
			score ++;
			randomMove(&seed);
			updateSeedScore(pScreen, &scoreTexte, score, &ttfManager);
		}
		//On affiche l'ensemble
		SDL_RenderClear(pScreen->renderer);
		updateScreen(&character,&enemies,pScreen,&ttfManager,pGameOptions);
		SDL_RenderCopy(pScreen->renderer,seed.pTexture, NULL, &seed.rec);
		SDL_RenderCopy(pScreen->renderer,scoreTexte.pTexture, NULL, &scoreTexte.rec);
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
			//on print dans le renderer ce qu'on veut afficher pendant la pause
			updateScreen(&character,&enemies,pScreen,&ttfManager,pGameOptions);
			SDL_RenderCopy(pScreen->renderer, ttfManager.pauseTextL1, NULL, &ttfManager.pauseTextL1Rec);
			SDL_RenderCopy(pScreen->renderer, ttfManager.pauseTextL2, NULL, &ttfManager.pauseTextL2Rec);
			SDL_RenderCopy(pScreen->renderer, ttfManager.pauseTextL3, NULL, &ttfManager.pauseTextL3Rec);
			SDL_RenderCopy(pScreen->renderer,seed.pTexture, NULL, &seed.rec);
			pauseLoop(pGameState,pIn,pScreen);
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
		//On print l'affichage de fin de partie
		updateScreen(&character,&enemies,pScreen,&ttfManager,pGameOptions);
		SDL_RenderCopy(pScreen->renderer, ttfManager.playAgain, NULL, &ttfManager.playAgainRec);
		SDL_RenderCopy(pScreen->renderer, ttfManager.BAM, NULL, &ttfManager.BAMRec);
		SDL_RenderCopy(pScreen->renderer,seed.pTexture, NULL, &seed.rec);
		//On attend que l'utilisateur décide de rejouer ou non
		endGameLoop(pIn,pGameState,pScreen);
	}
}



