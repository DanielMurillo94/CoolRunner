#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"
#include "BaseObject.h"

class Obstacle : public BaseObject
{
private:
    Vector2 firstPosition{};

public:
    bool willScorePoint{true};

    Obstacle(Vector2 _position, float _width, float _height, float speed);
    virtual void Update(float deltaTime);
    virtual void Draw();
};

#endif