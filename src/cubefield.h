#ifndef CUBEFIELD_H
#define CUBEFIELD_H

#include "cube.h"
#include <SDL.h>
#include <SDL_ttf.h>


struct Game
{
    SDL_Window* window;
    SDL_Renderer* rend;

    TTF_Font* font;

    struct Cube* cube_list;
    size_t cubes_num;

    float speed;
    float x_velocity;

    int alive;

    size_t score;
};

struct Game* game_init();
void game_quit(struct Game* game);

void game_render(struct Game* game);
int game_handle_events(struct Game* game);

static void append_cube(struct Game* game, float x, float y, float z);
static struct Cube create_cube(float x, float y, float z);

static SDL_Texture* render_text(SDL_Renderer* rend, TTF_Font* font, const char* text, SDL_Color color);
static void display_text(struct Game* game, SDL_Point pos, const char* text, SDL_Color color);

static void reset_data(struct Game* game);
inline static void move_cube_to_horizon(struct Cube* cube);

inline static int randint(int min, int max);

#endif

