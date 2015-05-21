#include "screenFunctions.h"


void updateScreen(Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager){
	int i;
	
	//Efface le contenu de l'écran
	SDL_RenderClear(pScreen->renderer);
	
	//On ajoute les versions des sprites mises à jour
	SDL_RenderCopy(pScreen->renderer,pScreen->map,NULL,NULL);
	SDL_RenderCopy(pScreen->renderer,pCharacter->square,NULL,&pCharacter->squarePosition); // Copie du sprite grâce au SDL_Renderer
	
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		SDL_RenderCopy(pScreen->renderer,pEnemies->enemies[i],NULL,&(pEnemies->enemiesPosition[i]));
	}	
	SDL_RenderCopy(pScreen->renderer, pTTFManager->time, NULL, &pTTFManager->timeRec);
	SDL_RenderCopy(pScreen->renderer, pTTFManager->actualTime, NULL, &pTTFManager->actualTimeRec);
    
	//On réaffiche le tout 
	SDL_RenderPresent(pScreen->renderer);
}

void updateTTFManager(Screen* pScreen, TTFManager* pTTFManager,TimeManager* pTimeManager){
	SDL_Color color={255, 255, 255};
	SDL_Surface* surface;
	
	char date[10] = "";	
	
	//Le temps de jeu écoulé
	
	pTimeManager->playingTime = ((long) (SDL_GetTicks() - pTimeManager->debutTicks))/1000;
	sprintf(date, "%ld", pTimeManager->playingTime);

	surface = TTF_RenderText_Blended(pTTFManager->font,date,color);
	
	if(surface == NULL){
		fprintf(stderr,"Erreur création de la surface du texte du timer: %s\n",TTF_GetError());
		exit(1);
	}
	
	pTTFManager->actualTime = SDL_CreateTextureFromSurface(pScreen->renderer, surface);
	
	if(pTTFManager->actualTime == NULL){
		fprintf(stderr,"Erreur création de la texture du texte du timer: %s\n",TTF_GetError());
		exit(1);
	}
}
