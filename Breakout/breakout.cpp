#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "breakout.h"
#include "ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Game.h"

using namespace std;
using namespace sf;


unsigned int windowWidth, windowHeight;

constexpr int countBlocksX{ 11 };
constexpr int countBlocksY{ 5 };

constexpr float UPDATE_RATE{ (1.0f / 120.0f) * 1000.0f};  // 1/60 secs physics update rate
constexpr float UPDATE_LIMIT{ 10 };
constexpr float UPDATE_STEP{ 1.0f };

void testCollision(const Paddle& pad, Ball& ball)
{
    // If there's no collision, get out of the function
    if (!isIntersecting(pad, ball))
        return;

    // otherwise let's rebound the ball upwards
    ball.velocity.y = -ball.ballVelocity;

    // and let's direct it horizontally dependent on the
    // position where the paddle was hit

    if (ball.x() < pad.x())
        ball.velocity.x = -ball.ballVelocity;
    else
        ball.velocity.x = ball.ballVelocity; 

}

void testCollision(Brick& brick, Ball& ball, bool& brickHit)
{
    if (!isIntersecting(brick, ball))
        return;

    brick.destroyed = true;
    brickHit = true;

    float overlapLeft = ball.right() - brick.left();
    float overlapRight = brick.right() - ball.left();
    float overlapTop = ball.bottom() - brick.top();
    float overlapBottom = brick.bottom() - ball.top();

    // If the magnitude of the left overlap is smaller than
    // the right one we can safely assume the ball hit the
    // brick from the left
    bool ballFromLeft = abs(overlapLeft) < abs(overlapRight);

    // We can apply the same idea for the top/bottom collisions
    bool ballFromTop = abs(overlapTop) < abs(overlapBottom);

    float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
    float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

    if (abs(minOverlapX) < abs(minOverlapY))
        ball.velocity.x = ballFromLeft ? -ball.ballVelocity : ball.ballVelocity;
    else
        ball.velocity.y = ballFromTop ? -ball.ballVelocity : ball.ballVelocity;
}

int main()
{
    sf::Color colors[5] = { Color::Red, Color::Cyan, Color::Yellow, Color::Magenta, Color::Blue };

    vector<Brick> bricks;

    for (int x = 0; x < countBlocksX; ++x)
        for (int y = 0; y < countBlocksY; ++y)
            bricks.emplace_back((x + 1) * (Brick::blockWidth + 3) + 22,
                                (y + 3) * (Brick::blockHeight + 3),
                                colors[y]);
            
    //vector<VideoMode> videoModes = VideoMode::getFullscreenModes();
    //VideoMode bestVideoMode = videoModes[0];
    //windowWidth = bestVideoMode.width;
    //windowHeight = bestVideoMode.height;
    windowWidth = 800;
    windowHeight = 600;
    RenderWindow window{ {windowWidth, windowHeight}, "Breakout - 1", Style::Titlebar | Style::Close };
    //RenderWindow window{ { windowWidth, windowHeight }, "Breakout - 1", Style::Fullscreen };
    window.setFramerateLimit(240);
    //window.setVerticalSyncEnabled(true);

    Ball ball{ windowWidth / 3.f, windowHeight / 2.f };
    Paddle paddle{ windowWidth / 2.f, windowHeight - 50.f };

    // Game loop
    bool gameRunning = true;
    FrameTime lastFT{ 0.0f };
    FrameTime totalTime{ 0.0f };
    int updateCount{ 0 };

    while (gameRunning)
    {
        auto timePoint1(chrono::high_resolution_clock::now());
        window.clear(Color::Black);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                gameRunning = false;
                break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            gameRunning = false;

        ball.update(lastFT);
        paddle.update(lastFT);
        testCollision(paddle, ball);
        bool brickHit = false;
        for (auto& brick : bricks)
            testCollision(brick, ball, brickHit);
        if (brickHit)
            bricks.erase(remove_if(begin(bricks), end(bricks),
                [](const Brick& brick) { return brick.destroyed; }),
                end(bricks));
        
        window.draw(ball.shape);
        window.draw(paddle.shape);
        for (auto& brick : bricks) 
            window.draw(brick.shape);

        window.display();

        

        auto timePoint2(chrono::high_resolution_clock::now());
        auto elapsedTIme(timePoint2 - timePoint1);
        FrameTime ft{ chrono::duration_cast<chrono::duration<float, milli>>(elapsedTIme).count() };
        lastFT = ft;
        auto ftSeconds(ft / 1000.0f);
        auto fps(1.0f / ftSeconds);

        window.setTitle("FT: " + to_string(ft) + "  FPS: " + to_string(fps));
    }

    return 0;
}
