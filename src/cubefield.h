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
};

struct Game* game_init();
void game_quit(struct Game* game);

void game_render(struct Game* game);
int game_handle_events();

static void append_cube(struct Game* game);
static struct Cube create_cube(float x, float y, float z);

#endif

