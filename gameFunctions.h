#ifndef gameFunctions
#define gameFunctions
 
#include "lib.h"

/** Met à jour les évenements du jeu **/
void updateInput(Input * in);

/** Vérifie toutes les collisions entre les objets du jeu **/
void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState);
void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision * pCollision, GameState *pGameState);
void addEnemy(Enemies * enemies);
void enemiesCollision(Enemies *pEnemies);
void moveEnemies(Enemies *pEnemies);
void endGame(Screen *pScreen,MusicManager *pMusicManager);
void moveCharacter(Input* pIn,Collision* pCollision,Character* pCharacter);


#endif
