#include "cubefield.h"
#include <time.h>


struct Game* game_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    struct Game* game = malloc(sizeof(struct Game));
    game->window = SDL_CreateWindow("Cubefield", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    game->rend = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(game->rend);
    SDL_RenderPresent(game->rend);

    game->font = TTF_OpenFont("res/font.ttf", 16);

    game->cube_list = 0;
    game->cubes_num = 0;

    game->speed = 0.05f;
    game->x_velocity = 0.f;

    game->alive = 1;

    game->score = 0;

    srand(time(0));

    return game;
}


void game_render(struct Game* game)
{
    SDL_RenderClear(game->rend);

    SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
    SDL_RenderDrawLine(game->rend, 0, 420, 800, 420);

    for (size_t i = 0; i < game->cubes_num; ++i)
    {
        struct Cube* cube = &game->cube_list[i];

        if (cube->points[0].z > 0.f && cube->points[0].z - game->speed <= 0.f && cube->points[0].x <= 0.f && cube->points[1].x >= 0.f)
        {
            game->alive = 0;
            game->speed = 0.05f;
            game->x_velocity = 0.f;
        }

        cube_render(game->rend, cube);
        cube_move(cube, 0.f, 0.f, -game->speed);

        if (cube->points[0].z < 0.f)
        {
            cube_move(&game->cube_list[i],
                -game->cube_list[i].points[0].x + (float)randint(-1000, 1000) / 100.f,
                0.f,
                10.f - game->cube_list[i].points[0].z
            );
        }
    }

    if (randint(0, 100) < 10 && game->cubes_num < 50)
    {
        int reused_cube = 0;

        for (size_t i = 0; i < game->cubes_num; ++i)
        {
            if (game->cube_list[i].points[0].z < 0.f)
            {
                cube_move(&game->cube_list[i],
                    -game->cube_list[i].points[0].x + (float)randint(-1000, 1000) / 100.f,
                    0.f,
                    10.f - game->cube_list[i].points[0].z
                );

                reused_cube = 1;
                break;
            }
        }

        if (!reused_cube)
            append_cube(game, (float)randint(-1000, 1000) / 100.f, 0.4f, 10.f);
    }

    if (game->alive)
    {
        game->speed += 0.00004f;
        static int accumulator = 0;
        ++accumulator;

        if (accumulator >= 10)
        {
            ++game->score;
            accumulator = 0;
        }
    }

    int length = snprintf(0, 0, "%ld", game->score);
    char* score = malloc(length + 7 + 1);
    snprintf(score, length + 7 + 1, "Score: %ld", game->score);
    display_text(game, (SDL_Point){ 20, 10 }, score, (SDL_Color){ 255, 255, 255 });

    if (!game->alive)
    {
        SDL_SetRenderDrawBlendMode(game->rend, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 150);

        SDL_Rect rect = { 0, 0, 800, 800 };
        SDL_RenderFillRect(game->rend, &rect);

        SDL_SetRenderDrawBlendMode(game->rend, SDL_BLENDMODE_NONE);

        display_text(game, (SDL_Point){ 350, 300 }, "Game over", (SDL_Color){ 255, 255, 255 });
        display_text(game, (SDL_Point){ 300, 400 }, "Press space to try again", (SDL_Color){ 255, 255, 255 });
    }

    free(score);

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
                if (game->alive)
                    game->x_velocity = 0.03f;
                break;
            case SDLK_LEFT:
                if (game->alive)
                    game->x_velocity = -0.03f;
                break;
            case SDLK_SPACE:
                if (!game->alive)
                {
                    game->alive = 1;
                    free(game->cube_list);
                    game->cube_list = 0;
                    game->cubes_num = 0;
                    game->score = 0;
                }
                break;
            }
        }
        break;
        case SDL_KEYUP:
        {
            switch (evt.key.keysym.sym)
            {
            case SDLK_RIGHT:
            case SDLK_LEFT:
                game->x_velocity = 0;
                break;
            }
        }
        break;
        }
    }

    for (size_t i = 0; i < game->cubes_num; ++i)
        cube_move(&game->cube_list[i], -game->x_velocity, 0.f, 0.f);

    return 1;
}


void game_quit(struct Game* game)
{
    free(game->cube_list);
    TTF_CloseFont(game->font);

    SDL_DestroyRenderer(game->rend);
    SDL_DestroyWindow(game->window);

    SDL_Quit();
    TTF_Quit();
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


static SDL_Texture* render_text(SDL_Renderer* rend, TTF_Font* font, const char* text, SDL_Color color)
{
    if (!text[0])
        return 0;

    SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);

    return tex;
}


static void display_text(struct Game* game, SDL_Point pos, const char* text, SDL_Color color)
{
    SDL_Texture* tex = render_text(game->rend, game->font, text, color);
    SDL_Rect tmp = { pos.x, pos.y };
    TTF_SizeText(game->font, text, &tmp.w, &tmp.h);
    SDL_RenderCopy(game->rend, tex, 0, &tmp);
    SDL_DestroyTexture(tex);
}


inline static int randint(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

