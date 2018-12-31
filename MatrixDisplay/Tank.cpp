#include "Tank.h"

using namespace std;

Tank::Tank(Point upperLeft) : Sprite("tank.png", Rect(upperLeft, Size(15, 8)))
{

}

Tank::~Tank()
{
}
