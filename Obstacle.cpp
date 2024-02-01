#include "raylib.h"
#include "Obstacle.h"
#include "BaseObject.h"
#include <iostream>

Obstacle::Obstacle(Vector2 _position, float _width, float _height) : BaseObject::BaseObject(_position, _width, _height)
{
    velocity = Vector2{-80.f, 0.f};
};

void Obstacle::Update(float deltaTime)
{
    BaseObject::Update(deltaTime);
};

void Obstacle::Draw()
{
    DrawRectangle(position.x, position.y, 100, 100, BLUE);
}