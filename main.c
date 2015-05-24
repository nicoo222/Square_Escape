#include "lib.h"


// gcc main.c initFunctions.c gameFunctions.c screenFunctions.c  gameLoop.c menu.c unit.c -lSDL2 -lSDL2_mixer -lSDL2_ttf -o game -Wall -Wformat -Wextra
int main(int argc, char* argv[]){
	if(argc > 1 && strcmp(argv[1],"-h")){		
	}
	//Création des structures de jeu
	Character character;
	Enemies enemies;
	GameState gameState;
	GameOptions gameOptions;
	Screen screen;
	Collision collision;
	Input in;
	Menu menu;
	MusicManager musicManager;
	TTFManager ttfManager;
	TimeManager timeManager;
	
	//Chargement des composants SDL2
	windowInitialization(&screen);
	audioInitialization(&musicManager);
	ttfInitialization(&screen,&ttfManager);
	initPauseText(&screen, &ttfManager);
	characterInitialization(&character,&screen);
	enemiesInitialization(&enemies,&screen);
	
	//Chargement des images 
	loadMenu(&menu, &screen);
	updateScreenMenu(&menu,&screen);
	
	//fprintf(stderr,"Parce qu'avec un printf ça marche\n"); // NON MAIS WTF SERIEUX ??!
	
	// on donne une graine pour générer des nombres random
	srand(time(NULL));
	
	// Durée de la boucle de jeu en ms
	screen.frameDuration = 16;
	
	//Mise à 0 des des booléens des structures
	memset(&in,0,sizeof(in));
	memset(&gameState,0,sizeof(gameState));	
	
	//Initialisation des comportements par défaut
	memset(&gameOptions,0,sizeof(gameOptions));
	gameState.menu = 1;
	
	//boucle principale
	while(!in.quit){
		if(gameState.menu){
			menuLoop (&in, &gameState, &screen, &menu, &gameOptions);
		}
		//si on quitte pas on rentre dans une partie
		if(!in.quit){
			updateTTFManager(&screen,&ttfManager,&timeManager,&enemies);
			if (gameOptions.mode == 0){
				mode0Loop(&in,&gameState,&character,&enemies,&screen,&collision,&musicManager,&ttfManager,&timeManager,&gameOptions);
			}
			if (gameOptions.mode == 1){
				mode1Loop(&in,&gameOptions,&screen,&gameState);
			}
		}
	}
	
	//Fin du jeu, une fois qu'on quitte le menu
	endGame(&screen,&musicManager,&ttfManager);
	
	return EXIT_SUCCESS;
}
