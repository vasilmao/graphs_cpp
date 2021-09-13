#include <SDL2/SDL.h>
#include "Plot.h"
#include <time.h>
#include <stdio.h>

enum SDL_init_errors {
    SDL_INIT_OK,
    CANT_INITIALIZE_SDL,
    CANT_CREATE_WINDOW,
    CANT_CREATE_RENDERER
};

class App {
private:
    Renderer* renderer;
    Plot big_plot;
    Plot small_plot;
    bool running;
    SDL_Color bg_color;

    int width;
    int height;

    void parseEvent(SDL_Event event);

public:
    App();

    void run();

    ~App();
};

// struct App {
//     SDL_Renderer* renderer;
// 	SDL_Window*   window;
//     bool   running;
//     int width;
//     int height;

//     SDL_Color bg_color;

//     Plot* plot_big;
//     Plot* plot_small;

//     int vectors_cnt;
    
// };