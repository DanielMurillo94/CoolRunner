#include "ObstacleManager.h"
#include "raylib.h"
#include <iostream>

ObstacleManager::ObstacleManager(int groundLevel, int windowWidth, Player *player) : groundLevel(groundLevel),
                                                                                     windowWidth(windowWidth),
                                                                                     player(player)
{

    std::cout << "Initializng obstacle manager with window width: " << windowWidth << "\n";
    sizeOfObstacleTypes = sizeof(obstacleTypes) / sizeof(obstacleTypes[0]);
    std::cout << "Length of obstacle types: " << sizeOfObstacleTypes << "\n";
}

void ObstacleManager::SpawnObstacle()
{
    int index = rand() % sizeOfObstacleTypes;
    ObstacleDimensions obstacleToSpawn = obstacleTypes[index];
    obstacles.push_back(Obstacle{Vector2{static_cast<float>(windowWidth), static_cast<float>(groundLevel - obstacleToSpawn.height)}, obstacleToSpawn.width, obstacleToSpawn.height, currentSpeed});
}

void ObstacleManager::PopOffscreenObstacle()
{
    if (obstacles.size() > 0 && obstacles.begin()->GetPosition().x < -100)
    {
        obstacles.pop_front();
    }
}

float ObstacleManager::RandomFloat(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

void ObstacleManager::TickTimer(float deltaTime)
{
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnTimeThreshold)
    {
        SpawnObstacle();
        spawnTimer = 0.f;
        spawnTimeThreshold = RandomFloat(minSpawnTime, maxSpawnTime);
        std::cout << "New spawn Threshold: " << spawnTimeThreshold << "\n";
    }
    speedTimer += deltaTime;
    if (speedTimer >= speedTimeThreshold)
    {
        currentSpeed = currentSpeed * speedMultiplier;
        speedTimer = 0.f;
        std::cout << "New speed: " << currentSpeed << "\n";
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

void ObstacleManager::Draw()
{
    for (std::list<Obstacle>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
    {
        obstacle->Draw();
    }
}