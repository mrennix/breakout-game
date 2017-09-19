#include "Paddle.h"
using namespace sf;

extern unsigned int windowWidth, windowHeight;


Paddle::Paddle(float mx, float my)
{
    shape.setPosition(mx, my);
    shape.setSize({ paddleWidth, paddleHeight });
    shape.setFillColor(Color::Green);
    shape.setOrigin(paddleWidth / 2.0f, paddleHeight / 2.0f);
}

Paddle::~Paddle()
{
}

void Paddle::update(FrameTime ft)
{
    shape.move(velocity * ft);

    // Only change velocity of paddle if it is inside the window
    if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
    {
        velocity.x = -paddleVelocity;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
    {
        velocity.x = paddleVelocity;
    }
    else
    {
        velocity.x = 0;
    }

}
