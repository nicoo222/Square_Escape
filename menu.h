#ifndef leMenu
#define leMenu
 
#include "lib.h"

//Prototypes des fonctions relatives à la gestion du menu

/** Chargement des elements du menu **/
void loadMenu(Menu *pMenu, Screen *pScreen);

/** Mise à jour des elements **/
void updateMenu(GameState *pGameState, Menu *pMenu, Screen *pScreen);

/** Mise à jour de l'affichage **/
void updateScreenMenu(Menu *pMenu, Screen *pScreen, GameState *pGamestate,GameOptions* pGameOptions);

#endif
