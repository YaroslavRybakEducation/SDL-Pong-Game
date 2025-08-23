#include "Player.hpp"

Player::Player()
{
    x = 10;
    width = 20;
    height = 80;
    winWidth = 800;
    winHeight = 600;
    y = winHeight / 2;
    playerRect = {x, y, width, height};
    speed = 8;
}

void Player::LimitMovement()
{
    if (playerRect.y < 80)
    {
        playerRect.y = 80;
    }
    else if (playerRect.y + playerRect.h > winHeight)
    {
        playerRect.y = winHeight - playerRect.h;
    }
}

void Player::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}

void Player::Move()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_W])
    {
        playerRect.y = playerRect.y - speed;
    }
    else if (keyState[SDL_SCANCODE_S])
    {
        playerRect.y = playerRect.y + speed;
    }
    LimitMovement();
}