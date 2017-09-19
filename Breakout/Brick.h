#pragma once
#include <SFML\Graphics.hpp>

class Brick
{
public:
    static constexpr float blockWidth{ 60.0f };
    static constexpr float blockHeight = 20.0f;

    Brick(float mx, float my, sf::Color color);
    ~Brick();
    void update();

    sf::RectangleShape shape;
    bool destroyed{ false };

    // useful "property" methods
    const float x()       const { return shape.getPosition().x; }
    const float y()       const { return shape.getPosition().y; }
    const float left()    const { return x() - shape.getSize().x / 2.0f; }
    const float right()   const { return x() + shape.getSize().x / 2.0f; }
    const float top()     const { return y() - shape.getSize().y / 2.0f; }
    const float bottom()  const { return y() + shape.getSize().y / 2.0f; }
};

