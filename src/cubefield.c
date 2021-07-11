#include "cubefield.h"


struct Game* game_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    struct Game* game = malloc(sizeof(struct Game));
    game->window = SDL_CreateWindow("Cubefield", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    game->rend = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(game->rend);
    SDL_RenderPresent(game->rend);

    game->cube = (struct Cube) {
        {
            { 0.f, 0.f, 10.f },
            { 1.f, 0.f, 10.f },
            { 1.f, 1.f, 10.f },
            { 0.f, 1.f, 10.f }
        }
    };

    return game;
}


void game_render(struct Game* game)
{
    SDL_RenderClear(game->rend);

    // only render anything in front of the camera
    if (game->cube.points[0].z > 0.0f)
    {
        cube_render(game->rend, &game->cube);
    }
    
    for (int i = 0; i < 4; ++i)
    {
        game->cube.points[i].z -= 0.01f;
    }

    SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);
    SDL_RenderPresent(game->rend);
}


int game_handle_events()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            return 0;
            break;
        }
    }

    return 1;
}


void game_quit(struct Game* game)
{
    SDL_DestroyRenderer(game->rend);
    SDL_DestroyWindow(game->window);

    SDL_Quit();
}

