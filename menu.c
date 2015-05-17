#include "menu.h"

void updateMenu(Input *pIn, GameState *pGameState){
	
	if (pIn->keys[SDL_SCANCODE_DOWN]){//on teste quelle touche est appuyée
		if (!pGameState->choice){
			pGameState->choice ++;
		}
	}
	
	if (pIn->keys[SDL_SCANCODE_UP]){
		if (pGameState->choice){
			pGameState->choice --;
		}
	}
	if (pIn->keys[SDL_SCANCODE_RETURN]){
		if (pGameState->choice == 0){
			pGameState->menu = 0;
		}
		else if (pGameState->choice == 1){
			pIn->quit = 1;
		}
	}
}

void loadMenu(Menu *pMenu, Screen *pScreen){
	SDL_Surface * startOn;
	SDL_Surface * startOff;
	SDL_Surface * quitOn;
	SDL_Surface * quitOff;
	
	startOn = SDL_LoadBMP("Pictures/StartOn.bmp");
	startOff = SDL_LoadBMP("Pictures/StartOff.bmp");
	quitOn = SDL_LoadBMP("Pictures/QuitOn.bmp");
	quitOff = SDL_LoadBMP("Pictures/QuitOff.bmp");
	
	if (startOn == NULL){
		fprintf(stderr,"Erreur chargement de l'image StartOn\n");
		exit(1);
	}
	if (startOff == NULL){
		fprintf(stderr,"Erreur chargement de l'image StartOff\n");
		exit(1);
	}
	if (quitOn == NULL){
		fprintf(stderr,"Erreur chargement de l'image QuitOn\n");
		exit(1);
	}
	if (quitOff == NULL){
		fprintf(stderr,"Erreur chargement de l'image QuitOff\n");
		exit(1);
	}

	//Mise en place des Render Start
	pMenu->Start[0]=SDL_CreateTextureFromSurface(pScreen->renderer,startOn);
	SDL_QueryTexture(pMenu->Start[0], NULL, NULL, &(pMenu->ButtonPos[0].w), &(pMenu->ButtonPos[0].h));
	pMenu->Start[1]=SDL_CreateTextureFromSurface(pScreen->renderer,startOff);
	SDL_QueryTexture(pMenu->Start[1], NULL, NULL, &(pMenu->ButtonPos[0].w), &(pMenu->ButtonPos[0].h));
	
	//Mise en place des Render Quit
	pMenu->Quit[0]=SDL_CreateTextureFromSurface(pScreen->renderer,quitOn);
	SDL_QueryTexture(pMenu->Quit[0], NULL, NULL, &(pMenu->ButtonPos[1].w), &(pMenu->ButtonPos[1].h));
	pMenu->Quit[1]=SDL_CreateTextureFromSurface(pScreen->renderer,quitOff);
	SDL_QueryTexture(pMenu->Quit[1], NULL, NULL, &(pMenu->ButtonPos[1].w), &(pMenu->ButtonPos[1].h));


	//Position des boutons
	
	pMenu->ButtonPos[0].x = 350;
	pMenu->ButtonPos[0].y = 250;
	pMenu->ButtonPos[1].x = 350;
	pMenu->ButtonPos[1].y = 350;	

}

void updateScreenMenu(Menu *pMenu, Screen *pScreen, GameState *pGamestate){
	
	//On efface le contenu de l'écran
	SDL_RenderClear(pScreen->renderer);
	
	//On ajoute les versions des sprites du menu
	if (pGamestate -> choice == 0){
		SDL_RenderCopy(pScreen->renderer,pScreen->map,NULL,NULL);
		SDL_RenderCopy(pScreen->renderer,pMenu->Start[0],NULL,&(pMenu->ButtonPos[0]));
		SDL_RenderCopy(pScreen->renderer,pMenu->Quit[1],NULL,&(pMenu->ButtonPos[1]));
	}
	if (pGamestate -> choice == 1){
		SDL_RenderCopy(pScreen->renderer,pScreen->map,NULL,NULL);
		SDL_RenderCopy(pScreen->renderer,pMenu->Start[1],NULL,&(pMenu->ButtonPos[0]));
		SDL_RenderCopy(pScreen->renderer,pMenu->Quit[0],NULL,&(pMenu->ButtonPos[1]));
	}
	
	//On réaffiche le tout 
    SDL_RenderPresent(pScreen->renderer);

}
