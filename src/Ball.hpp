#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>

class Ball
{
public:
    int radius;
    int x;
    int y;
    int speedX;
    int speedY;
    Ball();
    SDL_Texture *Draw(SDL_Renderer *renderer);
    SDL_Texture *Destroy();
    void Move();
    void Reset();
    SDL_Rect ballRect;
private:
    SDL_Texture *imageTexture;
    int winWidth;
    int winHeight;
};