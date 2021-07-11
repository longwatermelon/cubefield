#include "cubefield.h"


int main(int argc, char** argv)
{
    struct Game* game = game_init();

    int running = 1;
    while (running)
    {
        running = game_handle_events(game);
        game_render(game);
    }

    game_quit(game);
    free(game);

    return 0;
}

