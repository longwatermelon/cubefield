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
void cube_render_wireframe(SDL_Renderer* rend, struct Cube* cube);

void cube_move(struct Cube* cube, float x, float y, float z);

static SDL_FPoint project_point(struct Point* p);
static SDL_FPoint center_and_scale(SDL_FPoint point, int screen_w, int screen_h);

#endif

