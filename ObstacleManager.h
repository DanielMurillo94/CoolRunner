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
    float timer{};
    float spawnTimeThreshold{4};
    Player *player;
    ObstacleDimensions obstacleTypes[2]{{100, 100}, {200, 100}};
    int sizeOfObstacleTypes{};

    void TickTimer(float deltaTime);

public:
    ObstacleManager(int groundLevel, int windowWidth, Player *player);
    void SpawnObstacle();
    void PopOffscreenObstacle();
    void Update(float deltaTime);
    void Draw();
};