#include "screenFunctions.h"


void updateScreen(Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions){
	int i;
	//On ajoute les versions des sprites mises à jour
	SDL_RenderCopy(pScreen->renderer, pGameOptions->BG, NULL, &pGameOptions->BGRec);
	SDL_RenderCopy(pScreen->renderer,pCharacter->square,NULL,&pCharacter->squarePosition); // Copie du sprite grâce au SDL_Renderer
	
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		SDL_RenderCopy(pScreen->renderer,pEnemies->enemies[i],NULL,&(pEnemies->enemiesPosition[i]));
	}
	SDL_RenderCopy(pScreen->renderer, pTTFManager->time, NULL, &pTTFManager->timeRec);
	SDL_RenderCopy(pScreen->renderer, pTTFManager->squareNumber, NULL, &pTTFManager->squareNumberRec);
}

void updateTTFManager(Screen* pScreen, TTFManager* pTTFManager,TimeManager* pTimeManager,Enemies *pEnemies){
	SDL_Color color={255, 255, 255};
	char text[30] = "";
	char nombre [10] = "";
	
	//Le temps de jeu écoulé
	strcpy(text,"Temps : ");
	pTimeManager->playingTime = ((long) (SDL_GetTicks() - pTimeManager->debutTicks))/1000;
	sprintf(nombre, "%ld", pTimeManager->playingTime);
	strcat(text,nombre);
	pTTFManager->squareNumberRec.w=20*strlen(text);
	//printf("%d",strlen());
	SDL_Surface* pSurface;
	pSurface = TTF_RenderText_Blended(pTTFManager->font,text,color);
	SDL_DestroyTexture(pTTFManager->time);
	pTTFManager->time = SDL_CreateTextureFromSurface(pScreen->renderer, pSurface);
	if(pTTFManager->time == NULL){
		fprintf(stderr,"Erreur création de la texture du texte du timer: %s\n",TTF_GetError());
		exit(1);
	}
	
	//Le nombre d'ennemis
	strcpy(text,"Nombre d'ennemis : ");
	sprintf(nombre, "%d", pEnemies->numberOfEnemies);
	strcat(text,nombre);
	pTTFManager->squareNumberRec.w=20*strlen(text);
	SDL_Surface* pSurface2;
	pSurface2 = TTF_RenderText_Blended(pTTFManager->font,text,color);
	SDL_DestroyTexture(pTTFManager->squareNumber);
	pTTFManager->squareNumber = SDL_CreateTextureFromSurface(pScreen->renderer, pSurface2);
	if(pTTFManager->squareNumber == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	
	SDL_FreeSurface(pSurface2);
	SDL_FreeSurface(pSurface);
}




