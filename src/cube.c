#include "cube.h"


void cube_render(SDL_Renderer* rend, struct Cube* cube)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_FPoint prev_point;

    for (int i = 0; i < 4; ++i)
    {
        if (i - 1 >= 0)
        {
            prev_point = center_and_scale(project_point(&cube->points[i - 1]), 800, 800);
            SDL_FPoint current = center_and_scale(project_point(&cube->points[i]), 800, 800);

            SDL_RenderDrawLine(rend, prev_point.x, prev_point.y, current.x, current.y);
        }
        else
        {
            prev_point = center_and_scale(project_point(&cube->points[3]), 800, 800);
            SDL_FPoint current = center_and_scale(project_point(&cube->points[0]), 800, 800);

            SDL_RenderDrawLine(rend, prev_point.x, prev_point.y, current.x, current.y);
        }
    }
}


static SDL_FPoint project_point(struct Point* p)
{
    SDL_FPoint display;
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

