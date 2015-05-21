#ifndef gameFunctions
#define gameFunctions
 
#include "lib.h"

//Prototypes des fonctions relatives à l'affichage

void updateScreen(Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager);
void updateTTFManager(Screen* pScreen, TTFManager* pTTFManager,TimeManager *pTimeManager,long* pDebut);

#endif
