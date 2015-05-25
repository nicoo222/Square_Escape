#ifndef screenFunctions
#define screenFunctions
 
#include "lib.h"

//Prototypes des fonctions relatives à l'affichage

/** Mise à jour de l'affichage des textures **/
void updateScreen(Character *pCharacter,Enemies *pEnemies,Screen *pScreen,TTFManager *pTTFManager,GameOptions* pGameOptions);
void updateTTFManager(Screen* pScreen, TTFManager* pTTFManager,TimeManager* pTimeManager,Enemies *pEnemies);

/** Mise à jour du renderer **/
void refreshScren(Screen *pScreen);

/** Mise à jour pour le mode bonus **/
void updateSeedScore(Screen* pScreen,Texte* pTexte, int score,TTFManager* pTTFManager);

#endif
