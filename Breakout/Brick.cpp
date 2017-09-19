#include "Brick.h"

using namespace sf;

Brick::Brick(float mx, float my, Color color)
{

    shape.setPosition(mx, my);
    shape.setSize({ blockWidth, blockHeight });
    shape.setFillColor(color);
    shape.setOrigin(blockWidth / 2.0f, blockHeight / 2.0f);
}


Brick::~Brick()
{
}
