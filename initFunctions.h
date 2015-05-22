#ifndef initFunctions
#define initFunctions

#include "lib.h"

/** Fonction qui charge la SDL et crée une fenêtre de jeu **/
void gameInitialization(Screen *pScreen,GameState *pGameState,Input *pIn,GameOptions *pGameOptions);

/** Chargement du module audio et des sons **/
void audioInitialization(MusicManager *pMusicManager);

/** Chargement du module pour afficher du texte **/
void ttfInitialization(Screen * pScreen,TTFManager * pTTFManager);

/**Initialisation des ennemis **/
void enemiesInitialization(Enemies *pEnemies,Screen *pScreen);

/**Initialisation du cube personnage **/
void characterInitialization(Character *pCharacter,Screen *pScreen);

/**Initialisation du texte de la pause **/
void initPauseText(Screen* pScreen, TTFManager* pTTFManager);

#endif
