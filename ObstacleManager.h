#include <list>

#include "Obstacle.h"
#include "Player.h"

class ObstacleManager
{
private:
    int groundLevel{};
    float spawnRythm{10};
    std::list<Obstacle> obstacles{};
    int windowWidth{};
    float timer{};
    float spawnTimeThreshold{4};
    Player *player;

    void TickTimer(float deltaTime);

public:
    ObstacleManager(int groundLevel, int windowWidth, Player *player);
    void SpawnObstacle();
    void PopOffscreenObstacle();
    void Update(float deltaTime);
    void Draw();
};