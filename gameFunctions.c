#include "gameFunctions.h"


void gameInitialization(Objects * objects){
	putenv("SDL_VIDEO_WINDOW_POS=center"); //pour centrer la fenêtre
	
	// Initialisation de la SDL
	if(SDL_Init(SDL_INIT_VIDEO)== -1)
	{
		fprintf(stderr, "SDL can't be loaded: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	
	objects->window = SDL_CreateWindow("Square Escape",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_OPENGL);
    
    //Création du renderer
    objects->renderer = NULL;
    
    if((objects->renderer =  SDL_CreateRenderer( objects->window, 0, SDL_RENDERER_ACCELERATED))== NULL){
    	fprintf(stderr, "Erreur chargement de l'écran: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
    }

}

void objectsInitialization(Objects *objects){
	objects->map = SDL_LoadBMP("Pictures/map.bmp");
	objects->square = SDL_LoadBMP("Pictures/blueSquare.bmp");
	
	objects->mapTexture = SDL_CreateTextureFromSurface(objects->renderer,objects->map);
	objects->squareTexture = SDL_CreateTextureFromSurface(objects->renderer,objects->square);
	
	objects->squarePosition.x=objects->screen->w / 2 - objects->square->w / 2;
	
	SDL_RenderCopy(objects->renderer,objects->mapTexture,NULL,NULL);
	SDL_RenderCopy(objects->renderer,objects->squareTexture,NULL,&objects->squarePosition); // Copie du sprite grâce au SDL_Renderer
	SDL_BlitSurface(objects->square,NULL,objects->map,&objects->squarePosition); // Copie du sprite
}


void updateInput(int *exitGame)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
	switch(event.type)
        {
            case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_CLOSE)
				            *exitGame = 1;
				break;
        }
    }
}

void endGame(Objects * objects){
	SDL_DestroyWindow(objects->window);
    SDL_Quit();  
}
