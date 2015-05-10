#ifndef gameFunctions
#define gameFunctions
 
#include "gameStructures.h"

//Prototypes des fonctions propres au jeu

void gameInitialization(Objects *objects);
void objectsInitialization(Objects *objects);
void updateInput(int *exitGame);
void endGame(Objects *objects);

#endif
