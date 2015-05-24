#ifndef unit
#define unit

#include "lib.h"

void moveUnit();
void checkBorderCollision(Unit* pUnit);
void checkCollision(Unit* pUnit1, Unit* pUnit2);
void randomMove(Unit* pUnit);

#endif
