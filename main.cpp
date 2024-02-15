#include "raylib.h"
#include "Player.h"
#include "ObstacleManager.h"
#include <string>

int main(int argc, char const *argv[])
{
    int windowWidth{800};
    int windowHeight{500};

    int groundLevel{450};

    Player player{Vector2{200, 400}, 350.f, 0.7f, groundLevel};
    ObstacleManager obstacles{groundLevel, windowWidth, &player};

    InitWindow(windowWidth, windowHeight, "Runner");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);

        player.Update(deltaTime);
        obstacles.Update(deltaTime);

        player.Draw();
        obstacles.Draw();

        std::string pointsText{"Points: "};
        pointsText.append(std::to_string(player.GetCurrentPoints()));
        DrawText(pointsText.c_str(), 100, 100, 100, BLACK);

        EndDrawing();
    }
    return 0;
}
