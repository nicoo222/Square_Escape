#include "initFunctions.h"

void gameInitialization(Screen *pScreen,GameState *pGameState,Input *pIn,GameOptions *pGameOptions){
	SDL_Surface * surface;
	
	putenv("SDL_VIDEO_WINDOW_POS=center"); //Pour centrer la fenêtre
	
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
	
	// heeem il me semble que le memset ne marche pas #pascal
	memset(pGameState,0,sizeof(*pGameState));
	memset(pIn,0,sizeof(*pIn));
	memset(pGameOptions,0,sizeof(*pGameOptions));
	pGameOptions->mode = 0;
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

void enemiesInitialization(Enemies *pEnemies,Screen *pScreen){
	int i;
	SDL_Surface * surface;
	
	surface=SDL_LoadBMP("Pictures/redSquare.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image des ennemis\n");
		exit(1);
	}
    
	//Initialisation des premiers ennemis
	for(i=0;i<MAX_ENEMIES;i++){
		pEnemies->enemies[i]=SDL_CreateTextureFromSurface(pScreen->renderer,surface);
		SDL_QueryTexture(pEnemies->enemies[i], NULL, NULL, &(pEnemies->enemiesPosition[i].w), &(pEnemies->enemiesPosition[i].h));
		pEnemies->way[i]=rand()%3 + 4;
		pEnemies->speed[i]=3;
		pEnemies->enemiesPosition[i].x=900;
		pEnemies->enemiesPosition[i].y=320;
	}
	
	//Initialisation des coordonées des premiers ennemis
	pEnemies->enemiesPosition[0].x=100;
	pEnemies->enemiesPosition[0].y=50;
	pEnemies->enemiesPosition[1].x=700;
	pEnemies->enemiesPosition[1].y=500;
	pEnemies->way[1]=rand()%8 + 1;
	pEnemies->way[1]=rand()%8 + 1;
	
	pEnemies->numberOfEnemies=2;
}

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