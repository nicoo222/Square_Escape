#ifndef gameLoop
#define gameLoop

#include "lib.h"

// boucle qui gère une partie normale
void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen, GameOptions *pGameOptions);
void endGameLoop(Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Screen *pScreen);
#endif
