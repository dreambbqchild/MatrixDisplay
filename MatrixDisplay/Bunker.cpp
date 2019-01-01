#include "Bunker.h"

#define LEFT_FOR_64_COL_MATRIX_WITH_4_BUNKERS 4
                                                                                                                     //Tank Height 8 + Bunker Height 11 = 19
Bunker::Bunker(int index) : Sprite("bunker.png", Rect(Point(LEFT_FOR_64_COL_MATRIX_WITH_4_BUNKERS + index * 14, 96 - 19), Size(12, 11)))
{
}


Bunker::~Bunker()
{
}
