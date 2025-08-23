#pragma once
#include <SDL2/SDL.h>

#include "Player.hpp"
#include "Ball.hpp"

class CPU : public Player
{
public:
    int x;
    int y;
    int width;
    int height;
    int speed;
    CPU();
    void Draw(SDL_Renderer *renderer);
    void Movement(Ball ball);
    SDL_Rect cpuRect;
private:
    int winWidth;
    int winHeight;
};