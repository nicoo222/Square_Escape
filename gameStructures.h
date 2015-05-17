#ifndef structures
#define structures
 
#include "const.h"


//Structures globales

//Structures qui gère les entrées claviers
typedef struct Input
{
	int keys[1024];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[6];
	int quit;
	int mouseMovement;
} Input;

typedef struct Character{
	SDL_Texture * square;
	SDL_Rect squarePosition;
}Character;

typedef struct Enemies{
	SDL_Texture * enemies[MAX_ENEMIES];
	SDL_Rect enemiesPosition[MAX_ENEMIES];
	int way[MAX_ENEMIES];
	int speed[MAX_ENEMIES];
	int numberOfEnemies;
}Enemies;

//Gère les collisions d'un objet
typedef struct Collision{
	int up;
	int down;
	int left;
	int right;
}Collision;


typedef struct Screen{
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * map;
	SDL_Rect mapPosition;
	int frameDuration;
}Screen;

typedef struct GameState{
	int lost;
	int waiting;
	int pause;
	int quit;
	double time;
}GameState;

#endif
