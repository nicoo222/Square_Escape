#ifndef gameLoop
#define gameLoop

#include "screenFunctions.h"
#include "lib.h"
#include "gameFunctions.h"

/** Fin de partie (jeu en cours **/
void endGameLoop(Input *pIn,GameState *pGameState,Screen *pScreen);

/** Boucle d'attente du menu **/
void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu,GameOptions* pGameOptions);

/** Boucle d'attente dans le sous menu option **/
void menuOptionLoop (Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu,GameOptions* pGameOptions);

/** Boucle de pause d'une partie **/
void pauseLoop(GameState* pGameState,Input* pIn,Screen *pScreen);

/** Boucles de jeu **/
void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager,GameOptions* pGameOptions);

void mode1Loop(Input *pIn,GameOptions* pGameOptions,Screen* pScreen, GameState* pGameState);

#endif
