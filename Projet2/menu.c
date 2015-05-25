#include "menu.h"

void updateMenu(Input *pIn, GameState *pGameState){
	
	if (pIn->keys[SDL_SCANCODE_DOWN]){//on teste quelle touche est appuyée
		if ( pGameState->menu == 1){
			if (pGameState->choice != 2){
				pGameState->choice ++;
			}
		}
		if ( pGameState->menu == 2){
			if (pGameState->choice != 1){
				pGameState->choice ++;
			}
		}
	}
	
	if (pIn->keys[SDL_SCANCODE_UP]){
		if (pGameState->menu == 1){
			if (pGameState->choice != 0){
				pGameState->choice --;
			}
		}
		if (pGameState->menu == 2){
			if (pGameState->choice != 0){
				pGameState->choice --;
			}
		}
	}
	if (pIn->keys[SDL_SCANCODE_RETURN]){
		if (pGameState->menu == 1) {		
			if (pGameState->choice == 0){
				pGameState->menu = 0;
			}
			else if (pGameState->choice == 1){
				pGameState->menu = 2;
				pGameState->choice = 0;
			}
			else if (pGameState->choice == 2){
				pIn->quit = 1;
			}
		}
		else if (pGameState->menu == 2) {
			if (pGameState->choice == 0) {
				if (pGameState->sChoice == 0){
					pGameState->sChoice = 1;
				} else { pGameState->sChoice = 0;}
			}
			if (pGameState->choice == 1){
				if (pGameState->bgChoice == 0){
					pGameState->bgChoice = 1;
				} else { pGameState->bgChoice = 0;}
			}
		}
	}
}

void loadMenu(Menu *pMenu, Screen *pScreen){


}


