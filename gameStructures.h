#ifndef structures
#define structures
 
#include "lib.h"


//Structures globales

//Structure qui gère les entrées claviers
typedef struct Input{
	int keys[1024];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[6];
	int quit;
	int mouseMovement;
} Input;

typedef struct MusicManager{
	Mix_Music * music [MAX_MUSIC]; //Les musiques
	Mix_Chunk * sound [MAX_SOUND]; //Les sons courts
	int currentMusic; //Permet de savoir quelle musique est en cours de lecture
}MusicManager;

typedef struct TimeManager{
	long debutTicks;
	long playingTime;
}TimeManager;

//Gestion affichages textes
typedef struct TTFManager{
	SDL_Texture* score;
	SDL_Texture* time;
	SDL_Texture* playAgain;
	SDL_Texture* BAM;
	SDL_Texture* squareNumber;
	SDL_Texture* pauseTextL1;
	SDL_Texture* pauseTextL2;
	SDL_Texture* pauseTextL3;
	SDL_Rect pauseTextL1Rec;
	SDL_Rect pauseTextL2Rec;
	SDL_Rect pauseTextL3Rec;
	SDL_Rect squareNumberRec;
	SDL_Rect BAMRec;
	SDL_Rect timeRec;
	SDL_Rect playAgainRec;
	TTF_Font* font;
}TTFManager;

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
	int frameDuration;
}Screen;

typedef struct GameState{
	int lost;
	int waiting;
	int pause;
	int quit;
	int menu;
	//0 : hors du menu
	//1 : dans le menu principale
	//2 : dans le menu options
	int choice;
	int bgChoice;
	int sChoice;
	double time;
}GameState;

typedef struct GameOptions{
	int mode;
	int BGChoice;
	SDL_Texture* BG;
	SDL_Rect BGRec;
}GameOptions;

//liste des structures qui gèrent les objets du jeu
typedef struct Character{
	SDL_Texture * square;
	SDL_Rect squarePosition;
}Character;

typedef struct Unit{
	SDL_Texture* pTexture;
	SDL_Rect rec;
}Unit;

typedef struct Texte{
	int flag;
	SDL_Texture* pTexture;
	SDL_Rect rec;
}Texte;

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
	SDL_Rect BGChoiceRec;
	SDL_Texture *Selection;
	SDL_Rect ButtonPos[6];
	SDL_Texture* menuBG;
	SDL_Rect menuBGRec;
	
}Menu;


#endif
