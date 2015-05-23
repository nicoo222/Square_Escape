#ifndef gameLoop
#define gameLoop

#include "screenFunctions.h"
#include "lib.h"
#include "gameFunctions.h"

// boucle qui gère une partie normale
void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions);
void menuLoop(Input *pIn,GameState *pGameState, Screen *pScreen, Menu* pMenu);
void pauseLoop(GameState* pGameState,Input* pIn,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions);
void mode0Loop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen,Collision *pCollision,MusicManager *pMusicManager,TTFManager * pTTFManager,TimeManager *pTimeManager,GameOptions* pGameOptions);
void mode1Loop(Input *pIn,GameOptions* pGameOptions,Screen* pScreen, GameState* pGameState);

#endif
