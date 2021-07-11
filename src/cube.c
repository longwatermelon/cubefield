#include "cube.h"


void cube_render(SDL_Renderer* rend, struct Cube* cube)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    
    SDL_FPoint p3 = center_and_scale(project_point(&cube->points[3]), 800, 800);
    SDL_FPoint p0 = center_and_scale(project_point(&cube->points[0]), 800, 800);
    SDL_FPoint p1 = center_and_scale(project_point(&cube->points[1]), 800, 800);

    float rate = (p3.x - p0.x) / (p3.y - p0.y);
    float offset = 0.f;

    if ((p1.x + offset) - (p0.x - offset) > 800)
        return;

    for (int i = p0.y; i < p3.y; ++i)
    {
        offset += rate;
        SDL_RenderDrawLine(rend, p0.x - offset, i, p1.x + offset, i);
    }
}


void cube_move(struct Cube* cube, float x, float y, float z)
{
    for (int i = 0; i < 4; ++i)
    {
        cube->points[i].x += x;
        cube->points[i].y += y;
        cube->points[i].z += z;
    }
}


static SDL_FPoint project_point(struct Point* p)
{
    SDL_FPoint display;
    // take shortcut because i dont need the customizability of a projection matrix
    display.x = p->x / p->z;
    display.y = p->y / p->z;

    return display;
}


static SDL_FPoint center_and_scale(SDL_FPoint point, int screen_w, int screen_h)
{
    point.x += 1;
    point.y += 1;

    point.x *= 0.5f * screen_w;
    point.y *= 0.5f * screen_h;

    return point;
}

