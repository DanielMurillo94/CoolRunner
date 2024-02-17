#include "raylib.h"
#include "Player.h"
#include "ObstacleManager.h"
#include <string>

typedef enum GameScreen
{
    TITLE_SCREEN = 0,
    GAMEPLAY_SCREEN
};

int main(int argc, char const *argv[])
{
    int windowWidth{800};
    int windowHeight{500};

    InitWindow(windowWidth, windowHeight, "Runner");
    SetTargetFPS(60);

    GameScreen currentScreen = TITLE_SCREEN;

    int groundLevel{450};
    Player player{Vector2{200, 400}, 350.f, 0.7f, groundLevel};
    ObstacleManager obstacles{groundLevel, windowWidth, &player};

    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case TITLE_SCREEN:
        {
            // DrawText("TITLE SCREEN!", 100, 100, 50, BLACK);
            if (IsKeyPressed(KEY_SPACE))
            {
                currentScreen = GAMEPLAY_SCREEN;
                player.FullReset();
                obstacles.FullReset();
            }
        }
        break;
        case GAMEPLAY_SCREEN:
        {
            const float deltaTime{GetFrameTime()};
            player.Update(deltaTime);
            obstacles.Update(deltaTime);
            if (!player.IsAlive())
            {
                currentScreen = TITLE_SCREEN;
            }
        }
        break;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (currentScreen)
        {
        case TITLE_SCREEN:
        {
            DrawText("TITLE SCREEN!", 50, 100, 85, BLACK);
            if (player.GetRecord() > 0)
            {
                std::string recordText{"Record: "};
                recordText.append(std::to_string(player.GetRecord()));
                DrawText(recordText.c_str(), 50, 250, 85, BLACK);
            }
        }
        break;
        case GAMEPLAY_SCREEN:
        {
            player.Draw();
            obstacles.Draw();

            std::string pointsText{"Points: "};
            pointsText.append(std::to_string(player.GetCurrentPoints()));
            DrawText(pointsText.c_str(), 100, 100, 100, BLACK);
        }
        break;
        }
        EndDrawing();
    }
    return 0;
}
