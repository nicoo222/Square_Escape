#ifndef gameLoop
#define gameLoop

#include "lib.h"
#include "gameStructures.h"

// boucle qui gère une partie normale
void playLoop (Input *pIn,GameState *pGameState,int *pFrame,Character *pCharacter,Enemies *pEnemies,Collision *pCollision,Screen *pScreen);

#endif