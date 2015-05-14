#include "gameFunctions.c"

int main(int argc, char *argv[])
{
	Objects objects;
	sdfsdfsqgs
	gameInitialization(&objects);
	
	
    int frameTime, currentTime, frame = 0;
    int exitGame = 0;
    
    SDL_SetRenderDrawColor(objects.renderer, 255, 255, 255, 255);
    SDL_RenderClear(objects.renderer);
    objectsInitialization(&objects);
    
    while(!exitGame)
    {

        frameTime = SDL_GetTicks();
        frame++;
        
		updateInput(&exitGame);
		
        //SDL_UpdateWindowSurface(objects.window);
        
        //SDL_RenderClear(objects.renderer);
        SDL_RenderPresent(objects.renderer);

        currentTime = SDL_GetTicks();
        if(currentTime - frameTime < 1000/60)
            SDL_Delay(1000/60-currentTime+frameTime);
    }
    
    
    
    endGame(&objects);    
                       
	return EXIT_SUCCESS;
}
