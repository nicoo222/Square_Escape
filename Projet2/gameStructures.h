#ifndef structures
#define structures
 
#include "lib.h"


//Structures globales

//Structures qui gère les entrées claviers
typedef struct MusicManager{
	Mix_Music * music [MAX_MUSIC]; //Les musiques
	Mix_Chunk * sound [MAX_SOUND]; //Les sons courts
	int currentMusic; //Permet de savoir quelle musique est en cours de lecture
}MusicManager;

typedef struct TimeManager{
	long debutTicks;
	long playingTime;
}TimeManager;

typedef struct TTFManager{
	SDL_Texture * score;
	SDL_Texture * time;
	SDL_Texture * actualTime;
	SDL_Texture * playAgain;
	SDL_Rect timeRec;
	SDL_Rect actualTimeRec;
	TTF_Font *font;
}TTFManager;

typedef struct Input{
	int keys[1024];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[6];
	int quit;
	int mouseMovement;
} Input;

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
	int menu;
	int choice;
	int bgChoice;
	int sChoice;
	double time;
}GameState;

typedef struct GameOptions{
	int mode;
}GameOptions;

//liste des structures qui gère les objets du jeu
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

typedef struct Menu{
	SDL_Texture *Start;
	SDL_Texture *Quit;
	SDL_Texture *Option;
	SDL_Texture *Sounds;
	SDL_Texture *OnOff[2];
	SDL_Texture *BackGround;
	SDL_Texture *BgChoice[2];
	SDL_Texture *Selection;
	SDL_Rect ButtonPos[6];
	SDL_Texture* map;
	SDL_Rect mapRec;
	
}Menu;

#endif
