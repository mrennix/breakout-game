#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"

class Paddle
{
private:
    const float paddleWidth{ 60.f };
    const float paddleHeight{ 20.f };
    const float paddleVelocity{ .9f };

public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Paddle(float mx, float my);
    ~Paddle();
    void update(FrameTime ft);

    // useful "property" methods
    float x()      const { return shape.getPosition().x; }
    float y()      const { return shape.getPosition().y; }
    float left()   const { return x() - shape.getSize().x / 2.0f; }
    float right()  const { return x() + shape.getSize().x / 2.0f; }
    float top()    const { return y() - shape.getSize().y / 2.0f; }
    float bottom() const { return y() + shape.getSize().y / 2.0f; }
};

