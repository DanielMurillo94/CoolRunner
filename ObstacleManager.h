#include <list>

#include "Obstacle.h"
#include "Player.h"

struct ObstacleDimensions
{
    float height;
    float width;
};

class ObstacleManager
{
private:
    int groundLevel{};
    float spawnRythm{10};
    std::list<Obstacle> obstacles{};
    int windowWidth{};
    Player *player;
    ObstacleDimensions obstacleTypes[2]{{100, 100}, {200, 100}};
    int sizeOfObstacleTypes{};

    float timer{};
    float spawnTimeThreshold{5};
    float minSpawnTime{2.7f};
    float maxSpawnTime{16.f};

    void TickTimer(float deltaTime);

public:
    ObstacleManager(int groundLevel, int windowWidth, Player *player);
    void SpawnObstacle();
    void PopOffscreenObstacle();
    void Update(float deltaTime);
    void Draw();
    float RandomFloat(float min, float max);
};