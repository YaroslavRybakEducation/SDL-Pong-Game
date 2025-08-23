#pragma once
#include <SDL2/SDL.h>

class Player
{
protected:
    void LimitMovement();
public:
    int x;
    int y;
    int width;
    int height;
    int speed;
    Player();
    void Draw(SDL_Renderer *renderer);
    void Move();
    SDL_Rect playerRect;
private:
    int winWidth;
    int winHeight;
};