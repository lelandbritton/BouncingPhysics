#include "ball.h"
#include <raylib.h>
#include <iostream>
#include <cmath>

Ball::Ball() 
    : Ball(0, 0)
{
}

Ball::Ball(int startX, int startY)
    : x(startX)
    , y(startY)
    , speedX(2)
    , speedY(2)
    , radius(15) 
{
}

void Ball::Update() 
{
    x += speedX;
    y += speedY;
    
    Ball::Collision();
}

void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}

bool Ball::IsColliding(const Ball& other) const
{
    const int dx = other.x - x;
    const int dy = other.y - y;
    const int radiusSum = radius + other.radius;

    return dx * dx + dy * dy <= radiusSum * radiusSum;
}

void Ball::ResolveCollision(Ball& other)
{
    const int dx = other.x - x;
    const int dy = other.y - y;
    const int horizontalDistance = std::abs(dx);
    const int verticalDistance = std::abs(dy);
    const int minimumDistance = radius + other.radius;

    if (horizontalDistance > verticalDistance) {
        const int overlap = minimumDistance - horizontalDistance;
        const int direction = dx >= 0 ? 1 : -1;

        x -= direction * (overlap / 2);
        other.x += direction * (overlap - overlap / 2);

        if ((other.speedX - speedX) * dx < 0) {
            speedX *= -1;
            other.speedX *= -1;
        }
    } else {
        const int overlap = minimumDistance - verticalDistance;
        const int direction = dy >= 0 ? 1 : -1;

        y -= direction * (overlap / 2);
        other.y += direction * (overlap - overlap / 2);

        if ((other.speedY - speedY) * dy < 0) {
            speedY *= -1;
            other.speedY *= -1;
        }
    }
}

float Ball::GetSpeed() const
{
    float speed = std::sqrt(static_cast<float>(speedX * speedX + speedY * speedY));
    return speed;
}

void Ball::Collision(){

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if ((x + radius >= screenWidth) || (x - radius <= 0)) {
        x = (x + radius >= screenWidth) ? screenWidth - radius : radius;
        speedX *= -1;

        if (std::abs(speedX) < 50) {
            //speedX += speedX > 0 ? 1 : -1;
        }
    }
    
    if ((y + radius >= screenHeight) || (y - radius <= 0)) {
        y = (y + radius >= screenHeight) ? screenHeight - radius : radius;
        speedY *= -1;
        if (std::abs(speedY) < 50) {
            //speedY += speedY > 0 ? 1 : -1;
        }
    }
}
