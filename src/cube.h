#ifndef CUBE_H
#define CUBE_H

#include <SDL.h>


struct Point
{
    float x, y, z;
};

struct Cube
{
    // cubes are represented as squares
    struct Point points[4];
};

void cube_render(SDL_Renderer* rend, struct Cube* cube);

static SDL_FPoint project_point(struct Point* p);
static SDL_FPoint center_and_scale(SDL_FPoint point, int screen_w, int screen_h);

#endif

