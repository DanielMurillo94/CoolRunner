#include "Player.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <string>
#include <iostream>

Player::Player(Vector2 _position, float _jumpHeight, float _jumpTime, int _groundLevel) : jumpHeight(_jumpHeight),
                                                                                          jumpTime(_jumpTime),
                                                                                          jumpForce((-(2.0f * _jumpHeight) / _jumpTime)),
                                                                                          highJumpGravity((2.0f * _jumpHeight / (_jumpTime * _jumpTime))),
                                                                                          lowJumpGravity(highJumpGravity * 3),
                                                                                          currentGravity(highJumpGravity),
                                                                                          isInGround(true),
                                                                                          alive(true)
{
    width = 100.f;
    height = 100.f;
    originalHeight = _groundLevel - height;
    position = _position;
    velocity = Vector2{0.f, 0.f};
    area = Rectangle{};
    std::cout << "Constructing a player";
    Reset();
}

void Player::Jump()
{
    if (canJump)
    {
        currentGravity = highJumpGravity;
        velocity.y = jumpForce;
        isInGround = false;
        canJump = false;
    }
}

void Player::FallFaster()
{
    if (!isInGround)
    {
        currentGravity = lowJumpGravity;
    }
}

void Player::Reset()
{
    position.y = originalHeight;
    isInGround = true;
    canJump = true;
    velocity.y = 0;
    area.y = originalHeight;
}

void Player::LandOnObstacle(float height)
{
    position.y = height;
    canJump = true;
    area.y = position.y;
    velocity.y = 0;
}

void Player::EvaluateCollision(Obstacle *obstacle)
{
    if (lastFramePosition.y + height <= obstacle->GetPosition().y)
    {
        LandOnObstacle(obstacle->GetPosition().y - height);
        return;
    }
    Die();
}

void Player::Die()
{
    alive = false;
}

void Player::Update(float deltaTime)
{
    if (!alive)
    {
        return;
    }
    lastFramePosition = position;

    if (IsKeyPressed(KEY_SPACE))
    {
        Jump();
    }
    if (IsKeyReleased(KEY_SPACE))
    {
        FallFaster();
    }

    if (!isInGround)
    {
        velocity.y += (currentGravity * deltaTime);
    }

    BaseObject::Update(deltaTime);

    if (position.y >= originalHeight && !isInGround)
    {
        Reset();
    }
}

void Player::Draw()
{
    if (!alive)
    {
        return;
    }
    DrawRectangle(area.x, area.y, area.width, area.height, RED);
    for (int i = originalHeight; i > 0; i -= 100)
    {
        DrawLine(0, i, 1000, i, BLACK);
    }
}
