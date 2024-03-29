#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include "raylib.h"

class BaseObject
{
protected:
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
    float scale;
    Rectangle area;

public:
    BaseObject();
    BaseObject(Vector2 _position, float _width, float _height);
    Vector2 GetPosition() { return position; }
    Rectangle GetArea() { return area; }
    virtual void Update(float deltaTime);
    virtual void Draw() = 0;
};
#endif