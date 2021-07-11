#ifndef CUBEFIELD_H
#define CUBEFIELD_H

#include "cube.h"
#include <SDL.h>


struct Game
{
    SDL_Window* window;
    SDL_Renderer* rend;

    struct Cube cube;
};

struct Game* game_init();
void game_quit(struct Game* game);

void game_render(struct Game* game);
int game_handle_events();

#endif

