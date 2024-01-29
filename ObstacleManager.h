#include <list>

#include "Obstacle.h"

class ObstacleManager
{
private:
    int groundLevel{};
    float spawnRythm{10};
    std::list<Obstacle> obstacles{};
    int windowWidth{};
    float timer{};
    float spawnTimeThreshold{4};

    void TickTimer(float deltaTime);

public:
    ObstacleManager(int groundLevel, int windowWidth);
    void SpawnObstacle();
    void PopOffscreenObstacle();
    void Update(float deltaTime);
};