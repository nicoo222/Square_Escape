#include "initFunctions.h"
#include "const.h"

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
	
	memset(pGameState,0,sizeof(*pGameState));
	memset(pIn,0,sizeof(*pIn));
	memset(pGameOptions,0,sizeof(*pGameOptions));
	pGameOptions->mode = 0;
}

void audioInitialization(MusicManager *pMusicManager){
	int i;
	
	if(Mix_Init(MIX_INIT_MP3) == -1){
		fprintf(stderr, "Probleme initialisation de l'API SDL_Mixer %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){ //Initialisation de l'API Mixer
		fprintf(stderr, "Probleme chargement de l'API SDL_Mixer %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	
	
	//Chargement des musiques
	pMusicManager->music[0] = Mix_LoadMUS("Music/FunkAttitude.wav"); 
	pMusicManager->music[1] = Mix_LoadMUS("Music/Newgrounds.wav"); 
	
	for(i=0;i<MAX_MUSIC;i++){
		if(pMusicManager->music[i]==NULL){
	 		fprintf(stderr,"Erreur durant le chargement de la musique %d.\n",i);
	 		exit(1);
 		}
	}
	
	//Chargement des sons courts
 	pMusicManager->sound[0] = Mix_LoadWAV("Music/GameOver.wav");
 
 	for(i=0;i<MAX_SOUND;i++){
		Mix_VolumeChunk(pMusicManager->sound[i], MIX_MAX_VOLUME);
		if(pMusicManager->sound[i]==NULL){
	 		fprintf(stderr,"Erreur durant le chargement du son %d.\n",i);
	 		exit(1);
 		}
	}
 
 	
 	//Réglage du volume
 	Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
 	
 	//Lecture première musique de jeu 
 	Mix_PlayMusic(pMusicManager->music[0], -1); //Jouer infiniment la musique

}

void ttfInitialization(Screen * pScreen, TTFManager * pTTFManager){
	char* text;
	SDL_Color color={255, 255, 255};
	SDL_Surface * surface;
	
	//Initialisation de la librairie
	if(TTF_Init() == -1){
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(1);
	}
    
	pTTFManager->font = TTF_OpenFont("Font/Oetztype.ttf", 100);
	
	if(pTTFManager->font == NULL) { 
		fprintf(stderr, "Erreur chargement de la police d'écriture : %s\n", TTF_GetError());
    	exit(1);
	}
	
	pTTFManager->font = TTF_OpenFont("Font/Oetztype.ttf", 250);
	
	//Chargement texte fin de partie
	text="Voulez vous rejouer ? (y/n)";
	surface = TTF_RenderText_Blended(pTTFManager->font,text,color);
	pTTFManager->playAgain = SDL_CreateTextureFromSurface(pScreen->renderer, surface);
	if(pTTFManager->playAgain == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	
	text="CONTAAAACT!!!!!";
	surface = TTF_RenderText_Blended(pTTFManager->font,text,color);
	pTTFManager->BAM = SDL_CreateTextureFromSurface(pScreen->renderer, surface);
	if(pTTFManager->BAM == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	
	//qq init
	pTTFManager->squareNumberRec.x=20;
	pTTFManager->squareNumberRec.y=70;
	pTTFManager->squareNumberRec.h=50;
	pTTFManager->squareNumberRec.w=200;
	pTTFManager->BAMRec.x=100;
	pTTFManager->BAMRec.y=250;
	pTTFManager->BAMRec.h=50;
	pTTFManager->BAMRec.w=500;
	pTTFManager->playAgainRec.x=100;
	pTTFManager->playAgainRec.y=320;
	pTTFManager->playAgainRec.h=50;
	pTTFManager->playAgainRec.w=700;
	pTTFManager->timeRec.x=20;
	pTTFManager->timeRec.y=20;
	pTTFManager->timeRec.h=50;
	pTTFManager->timeRec.w=100;
}

void initPauseText(Screen* pScreen, TTFManager* pTTFManager){
	SDL_Color color={255, 255, 255};
	char text[30] = "";
	strcpy(text,"PAUSE");
	SDL_Surface* pSurface;
	pSurface = TTF_RenderText_Blended(pTTFManager->font,text,color);
	SDL_DestroyTexture(pTTFManager->pauseTextL1);
	pTTFManager->pauseTextL1 = SDL_CreateTextureFromSurface(pScreen->renderer, pSurface);
	if(pTTFManager->pauseTextL1 == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	pTTFManager->pauseTextL1Rec.x=300;
	pTTFManager->pauseTextL1Rec.y=150;
	pTTFManager->pauseTextL1Rec.h=50;
	pTTFManager->pauseTextL1Rec.w=100;
	
	strcpy(text,"P pour reprendre");
	SDL_Surface* pSurface2;
	pSurface2 = TTF_RenderText_Blended(pTTFManager->font,text,color);
	SDL_DestroyTexture(pTTFManager->pauseTextL2);
	pTTFManager->pauseTextL2 = SDL_CreateTextureFromSurface(pScreen->renderer, pSurface2);
	if(pTTFManager->pauseTextL2 == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	pTTFManager->pauseTextL2Rec.x=200;
	pTTFManager->pauseTextL2Rec.y=210;
	pTTFManager->pauseTextL2Rec.h=50;
	pTTFManager->pauseTextL2Rec.w=200;
	
	strcpy(text,"Q pour quitter");
	SDL_Surface* pSurface3;
	pSurface3 = TTF_RenderText_Blended(pTTFManager->font,text,color);
	SDL_DestroyTexture(pTTFManager->pauseTextL3);
	pTTFManager->pauseTextL3 = SDL_CreateTextureFromSurface(pScreen->renderer, pSurface3);
	if(pTTFManager->pauseTextL3 == NULL){
		fprintf(stderr,"Erreur création de la texture du texte. \n");
		exit(1);
	}
	pTTFManager->pauseTextL3Rec.x=200;
	pTTFManager->pauseTextL3Rec.y=270;
	pTTFManager->pauseTextL3Rec.h=50;
	pTTFManager->pauseTextL3Rec.w=200;
	
	SDL_FreeSurface(pSurface);
}

void enemiesInitialization(Enemies *pEnemies,Screen *pScreen){
	int i;
	SDL_Surface * surface;
	
	surface=SDL_LoadBMP("Pictures/redSquare.bmp");
	
	if (surface == NULL){
		fprintf(stderr,"Erreur chargement de l'image des ennemis\n");
		exit(1);
	}
    
	//Initialisation des ennemis
	for(i=0;i<MAX_ENEMIES;i++){
		pEnemies->enemies[i]=SDL_CreateTextureFromSurface(pScreen->renderer,surface);
		
		if(pEnemies->enemies[i] == NULL){
			fprintf(stderr,"Erreur chargement de création de la texture de l'ennemi %d.\n",i);
			exit(1);
		}
    
		SDL_QueryTexture(pEnemies->enemies[i], NULL, NULL, &(pEnemies->enemiesPosition[i].w), &(pEnemies->enemiesPosition[i].h));
		
		//Vitesse et direction de base 
		pEnemies->way[i]=rand()%3 + 4;
		pEnemies->speed[i]=3;
		pEnemies->enemiesPosition[i].x=900;
		pEnemies->enemiesPosition[i].y=320;
	}
	
	//Initialisation des coordonnées des premiers ennemis (2 au départ par défault)
	pEnemies->enemiesPosition[0].x=100;
	pEnemies->enemiesPosition[0].y=50;
	pEnemies->enemiesPosition[1].x=700;
	pEnemies->enemiesPosition[1].y=500;
	
	//Direction de mouvement aléatoire
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
