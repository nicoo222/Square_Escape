#include "gameFunctions.h"

/** Initialision de la SDL et de l'écran **/

void updateInput(Input* pIn){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_WINDOWEVENT:
			if(event.window.event == SDL_WINDOWEVENT_CLOSE){
				pIn->quit = 1;
			}
				break;
			case SDL_KEYDOWN:
				pIn->keys[event.key.keysym.scancode]=1;
				break;
			case SDL_KEYUP:
				pIn->keys[event.key.keysym.scancode]=0;
				break;
			default : 
				break;
		}
	}
}

void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState){

	memset(pCollision,0,sizeof(*pCollision));//Mise des élements de la structure à 0 (faux)
	
	enemiesCollision(pEnemies);
	characterCollision(pCharacter,pEnemies,pCollision,pGameState);
}

void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision *pCollision, GameState *pGameState){
	int i;
	
	//Collision bords de l'écran
	if (pCharacter->squarePosition.x < 0) pCollision->left=1;
	if (pCharacter->squarePosition.y < 0) pCollision->up=1;
	if (pCharacter->squarePosition.x + SQUARE_WIDTH > SCREEN_WIDTH ) pCollision->right=1;
	if (pCharacter->squarePosition.y + SQUARE_HEIGHT > SCREEN_HEIGHT) pCollision->down=1;
	
	//Collision avec un ennemi 
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		if((pCharacter->squarePosition.x < pEnemies->enemiesPosition[i].x + pEnemies->enemiesPosition[i].w)      // trop à droite
		&& (pCharacter->squarePosition.x + SQUARE_WIDTH > pEnemies->enemiesPosition[i].x) // trop à gauche
		&& (pCharacter->squarePosition.y < pEnemies->enemiesPosition[i].y + pEnemies->enemiesPosition[i].h) // trop en bas
		&& (pCharacter->squarePosition.y + SQUARE_HEIGHT > pEnemies->enemiesPosition[i].y)) //haut
		{  
			pGameState->lost=1;
		}
	}
}

void enemiesCollision(Enemies *pEnemies){
	int i;
	
	//Collision pour les ennemis avec le bord de l'écran
	//#immonde
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		// bord de droite
		if (pEnemies->enemiesPosition[i].x + SQUARE_WIDTH > SCREEN_WIDTH){
			if(pEnemies->way[i]==1) {
				pEnemies->way[i]=5+rand()%2*2-1;
			}else if (pEnemies->way[i]==2){
				pEnemies->way[i]=4 + rand()%2;
			}else if (pEnemies->way[i]==8) {
				pEnemies->way[i]=5 + rand()%2;
			}
		}
		// bord du haut
		if (pEnemies->enemiesPosition[i].y <= 0){
			if(pEnemies->way[i]== 3) {
				pEnemies->way[i]=7 + rand()%2*2-1;
			}else if (pEnemies->way[i]== 2){
				pEnemies->way[i]=7 + rand()%2;
			}else if (pEnemies->way[i]== 4) {
				pEnemies->way[i]=6 + rand()%2;
			}
		}
		// bord de gauche
		int newWay;
		if (pEnemies->enemiesPosition[i].x <= 0){
			newWay = rand()%3;
			if(pEnemies->way[i]==5) {
				pEnemies->way[i]=newWay?newWay:8;
			}else if (pEnemies->way[i]==4){
				pEnemies->way[i]=1 + rand()%2;
			}else if (pEnemies->way[i]==6){
				newWay = rand()%2;
				if(newWay == 0){
					pEnemies->way[i]=8;
				}else{
					pEnemies->way[i]=1;
				}
			}
		}
		// bord du bas
		if (pEnemies->enemiesPosition[i].y + SQUARE_HEIGHT > SCREEN_HEIGHT){
			if(pEnemies->way[i]==7) {
				pEnemies->way[i]=3 + rand()%2*2-1;
			}else if (pEnemies->way[i]==6){
				pEnemies->way[i]=3 + rand()%2;
			}else if (pEnemies->way[i]==8){
				pEnemies->way[i]=2 + rand()%2;
			}
		}
	}
}

void moveEnemies(Enemies *pEnemies){
	int i;
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		// le rapport de sqrt(2) = 1,41 est utilisé pour garder une vitesse à peut près constante
		// entre les diagonales et les directions cartésiennes
		if(pEnemies->way[i]==1){
			pEnemies->enemiesPosition[i].x+=pEnemies->speed[i]*1.41;
		}else if(pEnemies->way[i]==2){
			pEnemies->enemiesPosition[i].x+=pEnemies->speed[i];
			pEnemies->enemiesPosition[i].y-=pEnemies->speed[i];
		}else if(pEnemies->way[i]==3){
			pEnemies->enemiesPosition[i].y-=pEnemies->speed[i]*1.41;
		}else if(pEnemies->way[i]==4){
			pEnemies->enemiesPosition[i].x-=pEnemies->speed[i];
			pEnemies->enemiesPosition[i].y-=pEnemies->speed[i];
		}else if(pEnemies->way[i]==5){
			pEnemies->enemiesPosition[i].x-=pEnemies->speed[i]*1.41;
		}else if(pEnemies->way[i]==6){
			pEnemies->enemiesPosition[i].x-=pEnemies->speed[i];
			pEnemies->enemiesPosition[i].y+=pEnemies->speed[i];
		}else if(pEnemies->way[i]==7){
			pEnemies->enemiesPosition[i].y+=pEnemies->speed[i]*1.41;
		}else if(pEnemies->way[i]==8){
			pEnemies->enemiesPosition[i].x+=pEnemies->speed[i];
			pEnemies->enemiesPosition[i].y+=pEnemies->speed[i];
		}
	}
}

void addOneEnemy(Enemies *pEnemies){
	if(pEnemies->numberOfEnemies < MAX_ENEMIES){
		pEnemies->numberOfEnemies++;
	}
}

void moveCharacter(Input* pIn,Collision* pCollision,Character* pCharacter){
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
}

void endGame(Screen *pScreen,MusicManager *pMusicManager,TTFManager * pTTFManager){
	int i;
	
	SDL_DestroyWindow(pScreen->window);
	
	for(i=0;i<MAX_MUSIC;i++){
		Mix_FreeMusic(pMusicManager->music[i]); //Libération des pointeurs de l'API mixer
	}
	
	for(i=0;i<MAX_SOUND;i++){
		Mix_FreeChunk(pMusicManager->sound[i]); //Libération des pointeurs de l'API mixer
	}
	
	TTF_CloseFont(pTTFManager->font);
	TTF_Quit(); 
	Mix_CloseAudio();
    SDL_Quit();  
}

