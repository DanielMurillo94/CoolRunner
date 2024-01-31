#include "ObstacleManager.h"
#include "raylib.h"
#include <iostream>

ObstacleManager::ObstacleManager(int groundLevel, int windowWidth, Player *player) : groundLevel(groundLevel),
                                                                                     windowWidth(windowWidth),
                                                                                     player(player)
{

    std::cout << "Initializng obstacle manager with window width: " << windowWidth << "\n";
}

void ObstacleManager::SpawnObstacle()
{
    obstacles.push_back(Obstacle{Vector2{static_cast<float>(windowWidth), static_cast<float>(groundLevel - 100)}, 100.f, 100.f});
}

void ObstacleManager::PopOffscreenObstacle()
{
    if (obstacles.size() > 0 && obstacles.begin()->GetPosition().x < -100)
    {
        obstacles.pop_front();
    }
}

void ObstacleManager::TickTimer(float deltaTime)
{
    timer += deltaTime;
    if (timer >= spawnTimeThreshold)
    {
        SpawnObstacle();
        timer = 0.f;
    }
}

void ObstacleManager::Update(float deltaTime)
{
    for (std::list<Obstacle>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
    {
        obstacle->Update(deltaTime);
        if (CheckCollisionRecs(obstacle->GetArea(), player->GetArea()))
        {
            player->EvaluateCollision(&(*obstacle));
        }
    }
    TickTimer(deltaTime);
    PopOffscreenObstacle();
}