#include "ball.h"

using namespace sf;

extern unsigned int windowWidth, windowHeight;

Ball::Ball(float mX, float mY)
{
    shape.setPosition(mX, mY);
    shape.setRadius(ballRadius);
    shape.setFillColor(Color::White);
    shape.setOrigin(ballRadius, ballRadius);
}


Ball::~Ball()
{
}

void Ball::update(FrameTime ft)
{
    shape.move(velocity * ft);

    // Test for hitting left or right wall
    if (left() < 0)
        velocity.x = ballVelocity;
    else if (right() > windowWidth)
        velocity.x = -ballVelocity;
    // Test for hitting top or bottom wall
    else if (top() < 0)
        velocity.y = ballVelocity;
    else if (bottom() > windowHeight)
        velocity.y = -ballVelocity;
}