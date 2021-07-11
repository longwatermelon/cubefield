#ifndef CUBEFIELD_H
#define CUBEFIELD_H

#include "cube.h"
#include <SDL.h>


struct Game
{
    SDL_Window* window;
    SDL_Renderer* rend;

    struct Cube* cube_list;
    size_t cubes_num;

    float speed;

    float x_velocity;
};

struct Game* game_init();
void game_quit(struct Game* game);

void game_render(struct Game* game);
int game_handle_events(struct Game* game);

static void append_cube(struct Game* game, float x, float y, float z);
static void erase_cube(struct Game* game, int index);

static struct Cube create_cube(float x, float y, float z);
inline static int randint(int min, int max);

#endif

