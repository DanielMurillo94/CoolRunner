#include "raylib.h"
#include "BaseObject.h"

class Obstacle : public BaseObject
{
private:
    Vector2 firstPosition{};

public:
    Obstacle(Vector2 _position, float _width, float _height);
    virtual void Update(float deltaTime);
};