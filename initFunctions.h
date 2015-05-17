#ifndef initFunctions
#define initFunctions

#include "lib.h"

/** Fonction qui charge la SDL et crée une fenêtre de jeu **/
void gameInitialization(Screen *pScreen,GameState *pGameState,Input *pIn,GameOptions *pGameOptions);
void audioInitilization();
void enemiesInitialization(Enemies *pEnemies,Screen *pScreen);
void characterInitialization(Character *pCharacter,Screen *pScreen);

#endif
