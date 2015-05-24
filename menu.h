#ifndef leMenu
#define leMenu
 
#include "lib.h"

//Prototypes des fonctions relatives à la gestion du menu

void loadMenu(Menu *pMenu, Screen *pScreen);
void updateMenu(GameState *pGameState, Menu *pMenu, Screen *pScreen);
void updateScreenMenu(Menu *pMenu, Screen *pScreen);

#endif
