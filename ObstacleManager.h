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
    bool canSpawn{true};

    float spawnTimer{};
    float spawnTimeThreshold{5};

    float speedTimer{};
    float speedTimeThreshold{20.f};
    float speedMultiplier{1.5f};
    float currentSpeed{100.f}; // Pixels per second

    float haltTimer{};
    float haltTimeThreshold{3.f};

    void TickTimer(float deltaTime);
    void HaltSpawns(float deltaTime);

public:
    ObstacleManager(int groundLevel, int windowWidth, Player *player);
    void SpawnObstacle();
    void PopOffscreenObstacle();
    void Update(float deltaTime);
    void Draw();
    float RandomFloat(float min, float max);
    void FullReset();
};