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
