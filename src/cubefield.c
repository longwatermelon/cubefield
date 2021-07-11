#include "cubefield.h"
#include <time.h>


struct Game* game_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    struct Game* game = malloc(sizeof(struct Game));
    game->window = SDL_CreateWindow("Cubefield", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    game->rend = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(game->rend);
    SDL_RenderPresent(game->rend);

    game->cube_list = 0;
    game->cubes_num = 0;

    srand(time(0));
    append_cube(game, (float)randint(-100, 100) / 100.f, 0.f, 10.f);
    append_cube(game, (float)randint(-100, 100) / 100.f, 0.f, 10.f);

    return game;
}


void game_render(struct Game* game)
{
    SDL_RenderClear(game->rend);

    for (size_t i = 0; i < game->cubes_num; ++i)
    {
        struct Cube* cube = &game->cube_list[i];

        if (cube->points[0].z > 0.f)
        {
            cube_render(game->rend, cube);
        }

        cube_move(cube, 0.f, 0.f, -0.02f);
    }

    SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);
    SDL_RenderPresent(game->rend);
}


int game_handle_events(struct Game* game)
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            return 0;
            break;
        case SDL_KEYDOWN:
        {
            switch (evt.key.keysym.sym)
            {
            case SDLK_RIGHT:
                for (size_t i = 0; i < game->cubes_num; ++i)
                    cube_move(&game->cube_list[i], -0.1f, 0.f, 0.f);
                break;
            case SDLK_LEFT:
                for (size_t i = 0; i < game->cubes_num; ++i)
                    cube_move(&game->cube_list[i], 0.1f, 0.f, 0.f);
                break;
            }
        }
        break;
        }
    }

    return 1;
}


void game_quit(struct Game* game)
{
    free(game->cube_list);

    SDL_DestroyRenderer(game->rend);
    SDL_DestroyWindow(game->window);

    SDL_Quit();
}


static void append_cube(struct Game* game, float x, float y, float z)
{
    if (game->cube_list)
    {
        ++game->cubes_num;
        game->cube_list = realloc(game->cube_list, game->cubes_num * sizeof(struct Cube));
        game->cube_list[game->cubes_num - 1] = create_cube(x, y, z);
    }
    else
    {
        game->cubes_num = 1;
        game->cube_list = malloc(sizeof(struct Cube));
        game->cube_list[0] = create_cube(x, y, z);
    }
}


static struct Cube create_cube(float x, float y, float z)
{
    float size = 0.2f;

    return (struct Cube) {
        {
            { x - size, y - size, z },
            { x + size, y - size, z },
            { x + size, y + size, z },
            { x - size, y + size, z }
        }
    };
}


inline static int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

