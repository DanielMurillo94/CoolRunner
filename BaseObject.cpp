#include "BaseObject.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

BaseObject::BaseObject()
{
    std::cout << "Constructing a base object \n";
}

BaseObject::BaseObject(Vector2 _position, float _width, float _height) : position(_position),
                                                                         width(_width),
                                                                         height(_height)
{
}

void BaseObject::Update(float deltaTime)
{
    position = Vector2Add(position, Vector2Scale(velocity, deltaTime));
    area = Rectangle{position.x, position.y, width, height};
}