#pragma once

class Ball
{
public:
    Ball();
    Ball(int startX, int startY);
    void Update();
    void Collision();
    void ResolveCollision(Ball& other);
    void Draw() const;
    bool IsColliding(const Ball& other) const;
    float GetSpeed() const;

private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
};