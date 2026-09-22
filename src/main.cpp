#include <raylib.h>
#include "ball.h"
#include <set>
#include <vector>

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    std::vector<Ball> balls;
    std::set<std::pair<std::size_t, std::size_t>> previousCollisions;
    balls.emplace_back();
    int totalCollisionCount = 0;

    while (!WindowShouldClose())
    {
        for (Ball& currentBall : balls) {
            currentBall.Update();
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            balls.emplace_back(static_cast<int>(mousePosition.x),
                               static_cast<int>(mousePosition.y));
        }

        std::set<std::pair<std::size_t, std::size_t>> currentCollisions;
        for (std::size_t first = 0; first < balls.size(); ++first) {
            for (std::size_t second = first + 1; second < balls.size(); ++second) {
                if (balls[first].IsColliding(balls[second])) {
                    const auto pair = std::make_pair(first, second);
                    currentCollisions.insert(pair);
                    balls[first].ResolveCollision(balls[second]);

                    if (previousCollisions.find(pair) == previousCollisions.end()) {
                        ++totalCollisionCount;
                    }
                }
            }
        }
        previousCollisions = currentCollisions;

        BeginDrawing();
            ClearBackground(darkGreen);

            for (const Ball& currentBall : balls) {
                currentBall.Draw();
            }
            
            DrawText(TextFormat("Speed: %.2f", balls[0].GetSpeed()), 0, 0, 30, BLACK);
            DrawText(TextFormat("Collisions: %i", totalCollisionCount), 0, 35, 25, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}