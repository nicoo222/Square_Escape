#ifndef gameLoop
#define gameLoop

#include "gameStructures.h"

// boucle qui gère une partie normale
void playLoop (Input *pIn,GameState *pGameState,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen);
void endGameLoop(Input *pIn,GameState *pGameState);
#endif
