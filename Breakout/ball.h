#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"

class Ball
{
private:
    const float ballRadius{ 8.f };
    

public:
    Ball(float mX, float mY);
    ~Ball();
    void update(FrameTime ft);

    float ballVelocity{ .4f };
    sf::CircleShape shape;
    sf::Vector2f velocity{ -ballVelocity, -ballVelocity };
    

    // useful "property" methods
    float x()       const { return shape.getPosition().x; }
    float y()       const { return shape.getPosition().y; }
    float left()    const { return x() - shape.getRadius(); }
    float right()   const { return x() + shape.getRadius(); }
    float top()     const { return y() - shape.getRadius(); }
    float bottom()  const { return y() + shape.getRadius(); }

};

