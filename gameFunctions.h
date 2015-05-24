#ifndef gameFunctions
#define gameFunctions
 
#include "lib.h"

/** Met à jour les évenements du jeu **/
void updateInput(Input* pIn);

/** Vérifie toutes les collisions entre les objets du jeu **/
void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState);
void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision * pCollision, GameState *pGameState);
void addOneEnemy(Enemies *pEnemies);
void enemiesCollision(Enemies *pEnemies);
void moveEnemies(Enemies *pEnemies);
void moveCharacter(Input* pIn,Collision* pCollision,Character* pCharacter);
void endGame(Screen *pScreen,MusicManager *pMusicManager,TTFManager * pTTFManager);

#endif
