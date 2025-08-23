#include "CPU.hpp"

CPU::CPU()
{
    winWidth = 800;
    winHeight = 600;
    x = winWidth - 10 - 10 - 10;
    y = winHeight / 2;
    width = 20;
    height = 80;
    speed = 3;
    cpuRect = {x, y, width, height};
}

void CPU::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &cpuRect);
}

void CPU::Movement(Ball ball)
{
    if (ball.ballRect.y + ball.radius / 2 < cpuRect.y + cpuRect.h / 2 && cpuRect.y > 80)
    {
        cpuRect.y = cpuRect.y - speed;
    }
    if (ball.ballRect.y + ball.radius / 2 > cpuRect.y + cpuRect.h / 2 && cpuRect.y + cpuRect.h < winHeight)
    {
        cpuRect.y = cpuRect.y + speed;
    }
}