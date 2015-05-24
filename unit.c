#include "unit.h"

void moveUnit(){
}

int checkBorderCollision(Unit* pUnit){
  if(pUnit){
  }
  return 0;
}

//On check les collisions ET on trouve de quel coté l'unit1 (LA REFERENCE) percute l'unit2
int foundUnitCollision(Unit* pUnit1, Unit* pUnit2){
	if(pUnit1 && pUnit2){
	}
	/**
	// Gauche et Droite
	if (pUnit.rec.y + pUnit.rec.h > pCharacter->squarePosition.y
	&& pUnit.rec.y < pCharacter->squarePosition.y + SQUARE_HEIGHT){
		//Droite
		if(pUnit.rec.x + pUnit.rec.w > pCharacter->squarePosition.x){
		}
		//Gauche
		if(pUnit.rec.x < pCharacter->squarePosition.x + SQUARE_WIDTH){
		}
	}
	// Haut et Bas
	if (pUnit.rec.y < pCharacter->squarePosition.y + SQUARE_WIDTH
	&& pUnit.rec.x + pUnit.rec.w > pCharacter->squarePosition.x
	&& pUnit.rec.x < pCharacter->squarePosition.x + SQUARE_HEIGHT){
		//Haut
		if(){
		}
		//Bas
		if(){
		}
	}
	**/
	return 0;
}

//On check seulement si il y a collision avec une autre unité
int checkUnitCollision(Unit* pUnit1, Unit* pUnit2){
	if(pUnit1 && pUnit2){
	}
	return 0;
}

//On check seulement si il y a collision avec un character
int checkUnitCollisionWIthCharacter(Unit* pUnit, Character* pCharacter){
	if(pUnit->rec.x + pUnit->rec.w > pCharacter->squarePosition.x //trop à droite
	&& pUnit->rec.x < pCharacter->squarePosition.x + SQUARE_WIDTH //trop à gauche
	&& pUnit->rec.y < pCharacter->squarePosition.y + SQUARE_HEIGHT //trop haut
	&& pUnit->rec.y + pUnit->rec.h > pCharacter->squarePosition.y /**trop bas**/){
		return 1;
	}
	return 0;
}


void randomMove(Unit* pUnit){
	pUnit->rec.x=(int) (((double) rand()/RAND_MAX)*(PLAYING_AREA_WIDTH - pUnit->rec.w));
	pUnit->rec.y=(int) (((double) rand()/RAND_MAX)*(PLAYING_AREA_HEIGHT - pUnit->rec.h));
}
