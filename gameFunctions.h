#ifndef gameFunctions
#define gameFunctions
 
#include "lib.h"

/** Met à jour les évenements du jeu **/
void updateInput(Input* pIn);

/** Vérifie toutes les collisions entre les objets du jeu **/
void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState);

/** Vérifie les collisions par rapport au personnage **/
void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision * pCollision, GameState *pGameState);

/** Vérifie les collisions des ennemis **/
void enemiesCollision(Enemies *pEnemies);

/** Un nouvel ennemi apparait à l'écran **/
void addOneEnemy(Enemies *pEnemies);

/** Déplacement des ennemis **/
void moveEnemies(Enemies *pEnemies);

/** Déplacement du personnage **/
void moveCharacter(Input* pIn,Collision* pCollision,Character* pCharacter);

/** Fin de la partie **/
void endGame(Screen *pScreen,MusicManager *pMusicManager,TTFManager * pTTFManager);

#endif
