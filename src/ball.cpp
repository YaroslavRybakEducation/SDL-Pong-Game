#include "Ball.hpp"

using namespace std;

Ball::Ball()
{
    winWidth = 800;
    winHeight = 600;
    radius = 10;
    x = winWidth / 2;
    y = winHeight / 2;
    ballRect = {x, y, radius * 2, radius * 2};
    speedX = 5;
    speedY = 5;
}

SDL_Texture *Ball::Draw(SDL_Renderer *renderer)
{
    SDL_Texture *imageTexture = IMG_LoadTexture(renderer, "res/gfx/ball.png");
    SDL_RenderCopy(renderer, imageTexture, NULL, &ballRect);

    if (imageTexture == NULL)
    {
        cout << "Failed to create Texture: " << endl;
    }

    return imageTexture;
}

SDL_Texture *Ball::Destroy()
{
    SDL_DestroyTexture(imageTexture);
    return imageTexture;
}

void Ball::Move()
{
    ballRect.x = ballRect.x - speedX;
    ballRect.y = ballRect.y + speedY;

    if (ballRect.y + radius > winHeight - radius - 5)
    {
        speedY = -fabs(speedY);
    }
    else if (ballRect.y + radius < 80 + radius + 5)
    {
        speedY = fabs(speedY);
    }
    else if (ballRect.x + radius > winWidth - radius - 5)
    {
        speedX = -fabs(speedX);
    }
    else if (ballRect.x + radius < 0 + radius + 5)
    {
        speedX = fabs(speedX);
    }
}

void Ball::Reset()
{
    ballRect.x = winWidth / 2;
    ballRect.y = winHeight / 2;
}