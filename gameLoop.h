#ifndef gameLoop
#define gameLoop

#include "screenFunctions.h"
#include "lib.h"
#include "gameFunctions.h"

// boucle qui gère une partie normale
void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen, GameOptions *pGameOptions,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager);
void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager);
void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu);
void pauseLoop(GameState* pGameState,Input* pIn,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager);
void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager);

#endif
