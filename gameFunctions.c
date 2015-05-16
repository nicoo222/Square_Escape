#include "gameFunctions.h"


void gameInitialization(Screen *pScreen){
	SDL_Surface * surface;
	
	putenv("SDL_VIDEO_WINDOW_POS=center"); //pour centrer la fenêtre
	
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO)== -1)
	{
		fprintf(stderr, "SDL can't be loaded: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	
	pScreen->window = SDL_CreateWindow("Square Escape",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_OPENGL);
   
    //Création du renderer
    pScreen->renderer = NULL;
    
    if((pScreen->renderer =  SDL_CreateRenderer( pScreen->window, 0, SDL_RENDERER_ACCELERATED))== NULL){
    	fprintf(stderr, "Erreur chargement de l'écran: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
    }
	
	surface = SDL_LoadBMP("Pictures/fond.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image de fond\n");
		exit(1);
	}
	
	pScreen->map = SDL_CreateTextureFromSurface(pScreen->renderer,surface);
}

void audioInitilization(){
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		fprintf(stderr, "SDL audio mode can't be loaded: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
	Mix_Music *musique=Mix_LoadMUS("Music/newgrounds.mp3"); //
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

}
void updateInput(Input * in){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
		switch(event.type){
	        case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_CLOSE){
				        in->quit = 1;
		        }
				break;
			case SDL_KEYDOWN:
            	in->keys[event.key.keysym.scancode]=1;
				break;
			case SDL_KEYUP:
            	in->keys[event.key.keysym.scancode]=0;
				break;
			default : 
				break;
	    }
	}
}

void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState){

	memset(pCollision,0,sizeof(*pCollision));//Mise des élements de la structure à 0 (faux)
	
	characterCollision(pCharacter,pEnemies,pCollision,pGameState);
	enemiesCollision(pEnemies,pCollision);

}

void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision *pCollision, GameState *pGameState){
	int i;
	
	//Collision bords de l'écran
	if (pCharacter->squarePosition.x < 0) pCollision->left=1;
	if (pCharacter->squarePosition.y<0) pCollision->up=1;
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

void enemiesInitialization(Enemies *pEnemies,Screen *pScreen){
	int i;
	SDL_Surface * surface;
	
	surface=SDL_LoadBMP("Pictures/redSquare.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image des ennemis\n");
		exit(1);
	}
    
	//Initialisation des premiers ennemy
	for(i=0;i<MAX_ENEMIES;i++){
		pEnemies->enemies[i]=SDL_CreateTextureFromSurface(pScreen->renderer,surface);
		SDL_QueryTexture(pEnemies->enemies[i], NULL, NULL, &(pEnemies->enemiesPosition[i].w), &(pEnemies->enemiesPosition[i].h));
		pEnemies->way[i]=1;
		pEnemies->speed[i]=3;
	}
	
	//Initialisation des coordonées des premiers ennemis 
	pEnemies->enemiesPosition[0].x=100;
	pEnemies->enemiesPosition[0].y=50;
	pEnemies->enemiesPosition[1].x=200;
	pEnemies->enemiesPosition[1].y=100;
	
	pEnemies->numberOfEnemies=2;
}

void enemiesCollision(Enemies *pEnemies,Collision * pCollision){
	int i;
	
	//Collision pour les ennemis avec le bord de l'écran
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		if (pEnemies->enemiesPosition[i].x <= 0){
			if(pEnemies->way[i]==4) pEnemies->way[i]=1;
			else pEnemies->way[i]=2;
		}

		if (pEnemies->enemiesPosition[i].y <= 0){ 
			if(pEnemies->way[i]==3) pEnemies->way[i]=4;
			else pEnemies->way[i]=1;
		}

		if (pEnemies->enemiesPosition[i].x + SQUARE_WIDTH > SCREEN_WIDTH ){
			if(pEnemies->way[i]==2) pEnemies->way[i]=3;
			else pEnemies->way[i]=4;
		} 

		if (pEnemies->enemiesPosition[i].y + SQUARE_HEIGHT > SCREEN_HEIGHT){
			if(pEnemies->way[i]==1) pEnemies->way[i]=2;
			else pEnemies->way[i]=3;
		}
	}
}

void moveEnemies(Enemies *pEnemies){
	int i;
	
	for(i=0;i<pEnemies->numberOfEnemies;i++){
		if(pEnemies->way[i]==1){
			pEnemies->enemiesPosition[i].x+=2;
			pEnemies->enemiesPosition[i].y+=2;
		}
	
		else if(pEnemies->way[i]==2){
			pEnemies->enemiesPosition[i].x+=2;
			pEnemies->enemiesPosition[i].y-=2;
		}
		
		else if(pEnemies->way[i]==3){
			pEnemies->enemiesPosition[i].x-=2;
			pEnemies->enemiesPosition[i].y-=2;
		}
		else if(pEnemies->way[i]==4){
			pEnemies->enemiesPosition[i].x-=2;
			pEnemies->enemiesPosition[i].y+=2;
		}
	}
}


void endGame(Screen *pScreen){
	SDL_DestroyWindow(pScreen->window);
    SDL_Quit();  
}
