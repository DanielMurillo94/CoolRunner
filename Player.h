#include "raylib.h"
#include "BaseObject.h"

class Player : BaseObject
{
private:
    float jumpHeight; // Jump height in pixels
    float jumpTime;   // Time it'll take for the player to reach the max height of the jump
    float gravity{};
    float jumpForce{};
    bool isInGround{true};
    float originalHeight{};
    float highestHeight{1500};

public:
    Player(Vector2 _position, float _jumpHeight, float _jumpTime, int _groundLevel);
    void Jump();
    virtual void Update(float deltaTime);
};