#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "BaseObject.h"
#include "Obstacle.h"

class Player : public BaseObject
{
private:
    float jumpHeight; // Jump height in pixels
    float jumpTime;   // Time it'll take for the player to reach the max height of the jump
    float jumpForce{};

    const float highJumpGravity{};
    const float lowJumpGravity{};
    float currentGravity{};

    bool isInGround{true};
    bool canJump{false};
    float originalHeight{};
    float highestHeight{1500};

    Vector2 lastFramePosition{};

    bool alive{true};
    int currentPoints{0};

    void FallFaster();
    void Jump();
    void Reset();
    void LandOnObstacle(float height);

public:
    Player(Vector2 _position, float _jumpHeight, float _jumpTime, int _groundLevel);
    virtual void Update(float deltaTime);
    virtual void Draw();
    void Die();
    void EvaluateCollision(Obstacle *obstacle);
    void IncreasePoints(Obstacle *obstacle);
    int GetCurrentPoints() { return currentPoints; }
};

#endif