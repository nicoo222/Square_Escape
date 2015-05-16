#include "screenFunctions.h"


void characterInitialization(Character *pCharacter,Screen *pScreen){
	SDL_Surface * surface;
	
	surface = SDL_LoadBMP("Pictures/blueSquare.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image du personnage\n");
		exit(1);
	}
	
	surface->w=SQUARE_WIDTH;
	surface->h=SQUARE_HEIGHT;
	
	pCharacter->square = SDL_CreateTextureFromSurface(pScreen->renderer,surface);
	
	if(pCharacter->square == NULL){
		fprintf(stderr,"Erreur création de la texture du personnage\n");
		exit(1);
	}	
	
	pCharacter->squarePosition.x=250;//pObjects->screen->w / 2 - pObjects->square->w / 2;
	pCharacter->squarePosition.y=250;//pObjects->screen->h / 2 - pObjects->square->h / 2;
	
	SDL_QueryTexture(pCharacter->square, NULL, NULL, &(pCharacter->squarePosition.w), &(pCharacter->squarePosition.h));
	
	
}

void enemiesInitialization(Enemies *pEnemies,Screen *pScreen){
	int i;
	SDL_Surface * surface;
	
	surface=SDL_LoadBMP("Pictures/redSquare.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image des ennemis\n");
		exit(1);
	}
    
	//Initialisation du tableau des ennemis
	for(i=0;i<MAX_ENEMIES;i++){
		pEnemies->enemies[i]=SDL_CreateTextureFromSurface(pScreen->renderer,surface);
		SDL_QueryTexture(pEnemies->enemies[i], NULL, NULL, &(pEnemies->enemiesPosition[i].w), &(pEnemies->enemiesPosition[i].h));
		pEnemies->way[i]=2;
	}
	
	//Initialisation des premiers ennemis 
	pEnemies->enemiesPosition[0].x=100;
	pEnemies->enemiesPosition[0].y=50;
	pEnemies->enemiesPosition[1].x=200;
	pEnemies->enemiesPosition[1].y=100;
	
	pEnemies->numberOfEnemies=1;
}

void updateScreen(Character *pCharacter,Enemies *pEnemies,Screen *pScreen){
	int i;
	
	//Efface le contenu de l'écran
	SDL_RenderClear(pScreen->renderer);
	
	//On ajoute les versions des sprites mises à jour
	SDL_RenderCopy(pScreen->renderer,pScreen->map,NULL,NULL);
	SDL_RenderCopy(pScreen->renderer,pCharacter->square,NULL,&pCharacter->squarePosition); // Copie du sprite grâce au SDL_Renderer
	
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		SDL_RenderCopy(pScreen->renderer,pEnemies->enemies[i],NULL,&(pEnemies->enemiesPosition[i])); 
	}
	
	//On réaffiche le tout 
    SDL_RenderPresent(pScreen->renderer);
 
}
