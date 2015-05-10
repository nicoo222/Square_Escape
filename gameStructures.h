#ifndef structures
#define structures
 
#include "const.h"


//Structures globales

//Structures qui gère les entrées claviers
typedef struct Input
{
	int key[512];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[6];
	int quit;
	int mouseMovement;
} Input;

//Gère les collisions d'un objet
typedef struct Collision
{
	int up;
	int down;
	int left;
	int right;
}Collision;

//Pour tous les objets du jeu, on enregistre l'image + une forme rectangulaire permettant de gérer la position en (x,y)
typedef struct Objects
{
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * squareTexture;
	SDL_Texture * mapTexture;
	SDL_Surface *screen;
	SDL_Surface * square;
	SDL_Surface * map;
	SDL_Surface * enemies[MAX_ENEMIES];
	int way[MAX_ENEMIES]; 
	SDL_Rect squarePosition;
	SDL_Rect mapPosition;
	SDL_Rect enemiesPosition[MAX_ENEMIES];
}Objects;

typedef struct Game
{
	int lost;
	int waiting;
	int quit;
}Game;

#endif
