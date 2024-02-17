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
    SetRandomSeed((unsigned int)time(NULL));
}

void ObstacleManager::FullReset()
{
    canSpawn = true;
    spawnTimer = 0;
    speedTimer = 0;
    spawnTimeThreshold = 5;
    haltTimer = 0;
    speedMultiplier = 1.5f;
    currentSpeed = 100.f;
    obstacles.clear();
}

void ObstacleManager::SpawnObstacle()
{
    if (!canSpawn)
    {
        return;
    }
    int index = GetRandomValue(0, sizeOfObstacleTypes - 1);
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
    std::cout << "RANDOM FLOAT BETWEEN: " << min << " and "
              << max << "\n";
    float random = (float)GetRandomValue(1, 100);
    float diff = max - min;
    float scale = diff / 100;
    float newRandom = (random * scale) + min;
    return newRandom;
}

void ObstacleManager::TickTimer(float deltaTime)
{
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnTimeThreshold)
    {
        SpawnObstacle();
        spawnTimer = 0.f;
        Rectangle latestObstacle = obstacles.end()->GetArea();
        spawnTimeThreshold = RandomFloat((latestObstacle.width + 200) / currentSpeed, (windowWidth / currentSpeed) + 0.7f);
        std::cout << "New spawn Threshold: " << spawnTimeThreshold << "\n";
    }
    speedTimer += deltaTime;
    if (speedTimer >= speedTimeThreshold)
    {
        speedMultiplier = 1.5f;
        if (currentSpeed > 350.f)
        {
            speedMultiplier = 1.3f;
        }
        if (currentSpeed > 500.f)
        {
            speedMultiplier = 1.1f;
        }
        currentSpeed = currentSpeed * speedMultiplier;
        speedTimer = 0.f;
        std::cout << "New speed: " << currentSpeed << ":" << speedMultiplier << "\n";
        canSpawn = false;
    }
}

void ObstacleManager::HaltSpawns(float deltaTime)
{
    haltTimer += deltaTime;
    if (haltTimer >= haltTimeThreshold)
    {
        haltTimer = 0;
        canSpawn = true;
        spawnTimeThreshold = 0;
    }
}

void ObstacleManager::Update(float deltaTime)
{
    if (!canSpawn && obstacles.size() <= 0)
    {
        HaltSpawns(deltaTime);
        return;
    }
    for (std::list<Obstacle>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
    {
        obstacle->Update(deltaTime);
        if (CheckCollisionRecs(obstacle->GetArea(), player->GetArea()))
        {
            player->EvaluateCollision(&(*obstacle));
        }
        if (obstacle->GetPosition().x <= player->GetPosition().x)
        {
            player->IncreasePoints(&(*obstacle));
        }
    }
    TickTimer(deltaTime);
    PopOffscreenObstacle();
}

void ObstacleManager::Draw()
{
    if (!canSpawn && obstacles.size() <= 0)
    {
        DrawText("SPEED INCREASING!!", 40, 40, 40, RED);
    }
    for (std::list<Obstacle>::iterator obstacle = obstacles.begin(); obstacle != obstacles.end(); obstacle++)
    {
        obstacle->Draw();
    }
}

// void RegisterPoints(){
//     if(oneObstacle.position.x > player->position.x){
//         registerPoint(bool isInGroud)
//             Inside this function if isInGround
//     }
// }