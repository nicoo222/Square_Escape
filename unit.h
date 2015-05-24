#ifndef unit
#define unit

#include "lib.h"

void moveUnit();
int checkBorderCollision(Unit* pUnit);
int foundUnitCollision(Unit* pUnit1, Unit* pUnit2);
int checkUnitCollision(Unit* pUnit1, Unit* pUnit2);
int checkUnitCollisionWIthCharacter(Unit* pUnit1, Character* pCharacter);
void randomMove(Unit* pUnit);

#endif
