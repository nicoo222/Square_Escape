#ifndef gameFunctions
#define gameFunctions
 
#include "gameStructures.h"

//Prototypes des fonctions propres au jeu

/** Fonction qui charge la SDL et crée une fenêtre de jeu **/
void gameInitialization(Screen *pScreen,GameState *pGameState,Input *pIn,GameOptions *pGameOptions);

/** Met à jour les évenements du jeu **/
void updateInput(Input * in);

/** Vérifie toutes les collisions entre les objets du jeu **/
void checkCollision(Character *pCharacter,Enemies *pEnemies,Collision *pCollision,GameState * pGameState);
void characterCollision(Character *pCharacter, Enemies *pEnemies, Collision * pCollision, GameState *pGameState);
void addEnemy(Enemies * enemies);
void audioInitilization();
void enemiesCollision(Enemies *pEnemies);
void moveEnemies(Enemies *pEnemies);
void endGame(Screen *pScreen);
void enemiesInitialization(Enemies *pEnemies,Screen *pScreen);


#endif
