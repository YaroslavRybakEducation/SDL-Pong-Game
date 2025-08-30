#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

// Import Header files
#include "Player.hpp"
#include "Board.hpp"
#include "Ball.hpp"
#include "CPU.hpp"

using namespace std;

SDL_Surface *ScoreSurface = NULL;

int playerScore = 0;
int cpuScore = 0;

SDL_Texture *renderText(TTF_Font *font, SDL_Renderer *renderer)
{
    string scoreText = to_string(playerScore) + ":" + to_string(cpuScore);
    ScoreSurface = TTF_RenderText_Blended(font, scoreText.c_str(), {255, 255, 255, 255});
    SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(renderer, ScoreSurface);
    SDL_FreeSurface(ScoreSurface);

    SDL_Rect dst;

    dst.x = (800 - ScoreSurface->w) / 2;
    dst.y = 20;
    dst.w = ScoreSurface->w;
    dst.h = ScoreSurface->h;

    SDL_RenderCopy(renderer, fontTexture, NULL, &dst);
    return fontTexture;
}

int main(int argc, char *argv[])
{
    // Initialize
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        cout << "Failed to initialize. Error: " << SDL_GetError() << endl;
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cout << "Failed to initialize IMG. Error: " << IMG_GetError() << endl;
    }

    if (TTF_Init() != 0)
    {
        cout << "Failed to initlialize TTF. Error: " << TTF_GetError() << endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) > 0)
    {
        cout << "Failed to initialize Mix. Error: " << Mix_GetError() << endl;
    }

    SDL_Window *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Player player = Player();
    Ball ball = Ball();
    CPU cpu = CPU();

    Uint32 ms = 16; // 60 FPS

    TTF_Font *font = TTF_OpenFont("res/font/font.ttf", 60);

    if (font == NULL)
    {
        cout << "Failed to load font: " << TTF_GetError() << endl;
    }

    if (window == NULL)
    {
        cout << "Failed to create window. Error: " << SDL_GetError() << endl;
        return -1;
    }
    if (renderer == NULL)
    {
        cout << "Failed to create renderer. Error: " << SDL_GetError() << endl;
        return -1;
    }

    Mix_Chunk *winSound = Mix_LoadWAV("res/sfx/pScore.wav");
    Mix_Chunk *loseSound = Mix_LoadWAV("res/sfx/cpuScore.wav");

    if (winSound == NULL)
    {
        cout << "Failed to open sound: " << Mix_GetError() << endl;
    }
    if (loseSound == NULL)
    {
        cout << "Failed to open sound: " << Mix_GetError() << endl;
    }

    bool isRunning = true;

    SDL_Event event;

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
        }
        player.Move();
        ball.Move();
        cpu.Movement(ball);

        // Check for score increasing
        if (ball.ballRect.x < 0 + ball.radius)
        {
            // cout << "CPU Scored!" << endl;
            cpuScore++;
            Mix_PlayChannel(-1, loseSound, 0);
            SDL_Delay(1000);
            ball.Reset();
        }
        if (ball.ballRect.x > 800 - ball.radius - 20)
        {
            // cout << "Player scored!" << endl;
            playerScore++;
            Mix_PlayChannel(-1, winSound, 0);
            SDL_Delay(1000);
            ball.Reset();
        }

        // Check for ball collisions
        if (SDL_HasIntersection(&cpu.cpuRect, &ball.ballRect))
        {
            ball.speedX = fabs(ball.speedX);
        }
        else if (SDL_HasIntersection(&player.playerRect, &ball.ballRect))
        {
            ball.speedX = -fabs(ball.speedX);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(renderer);
        DrawBoard(renderer);
        player.Draw(renderer);
        ball.Draw(renderer);
        cpu.Draw(renderer);
        renderText(font, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(ms);
        ball.Destroy();
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    return 0;
}
