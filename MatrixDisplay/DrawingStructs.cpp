#include "DrawingStructs.h"


Movement operator |(Movement left, Movement right) { return static_cast<Movement>(static_cast<unsigned>(left) | static_cast<unsigned>(right)); }
Movement operator &(Movement left, Movement right) { return static_cast<Movement>(static_cast<unsigned>(left) & static_cast<unsigned>(right)); }
Movement operator ~(Movement m) { return static_cast<Movement>(~static_cast<unsigned>(m)); }

Button operator |(Button left, Button right) { return static_cast<Button>(static_cast<unsigned>(left) | static_cast<unsigned>(right)); }
Button operator &(Button left, Button right) { return static_cast<Button>(static_cast<unsigned>(left) & static_cast<unsigned>(right)); }
Button operator ~(Button m) { return static_cast<Button>(~static_cast<unsigned>(m)); }