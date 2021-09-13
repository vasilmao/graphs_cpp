#include "App.h"

void parseEvent(App* app, SDL_Event event);

#define OPEN_RGBA(x) x.r, x.g, x.b, x.a

const SDL_Color BG_COLOR = {185, 226, 235, 255};


const int WIDTH  = 800;
const int HEIGHT = 600;

const float SMALL_PLOT_X_MIN = -8.0;
const float SMALL_PLOT_X_MAX = 12.0;
const float SMALL_PLOT_Y_MIN = -3.0;
const float SMALL_PLOT_Y_MAX =  5.0;

const Rectf small_range_rect = {
    SMALL_PLOT_X_MIN,
    SMALL_PLOT_Y_MIN,
    SMALL_PLOT_X_MAX - SMALL_PLOT_X_MIN,
    SMALL_PLOT_Y_MAX - SMALL_PLOT_Y_MIN
};

const int SMALL_PLOT_SCREEN_X       = 450;
const int SMALL_PLOT_SCREEN_WIDTH   = 200;
const int SMALL_PLOT_SCREEN_Y       = 0;
const int SMALL_PLOT_SCREEN_HEIGHT  = 150;

const Recti small_screen_rect = {
    SMALL_PLOT_SCREEN_X,
    SMALL_PLOT_SCREEN_Y,
    SMALL_PLOT_SCREEN_WIDTH,
    SMALL_PLOT_SCREEN_HEIGHT,
};

const float BIG_PLOT_X_MIN   = -10.0;
const float BIG_PLOT_X_MAX   =  10.0;
const float BIG_PLOT_Y_MIN   = -10.0;
const float BIG_PLOT_Y_MAX   =  10.0;

const Rectf big_range_rect = {
    BIG_PLOT_X_MIN,
    BIG_PLOT_Y_MIN,
    BIG_PLOT_X_MAX - BIG_PLOT_X_MIN,
    BIG_PLOT_Y_MAX - BIG_PLOT_Y_MIN
};

const int BIG_PLOT_SCREEN_X       = 0;
const int BIG_PLOT_SCREEN_WIDTH   = 400;
const int BIG_PLOT_SCREEN_Y       = 0;
const int BIG_PLOT_SCREEN_HEIGHT  = 300;

const Recti big_screen_rect = {
    BIG_PLOT_SCREEN_X,
    BIG_PLOT_SCREEN_Y,
    BIG_PLOT_SCREEN_WIDTH,
    BIG_PLOT_SCREEN_HEIGHT,
};

float function_to_draw(float x) {
    return sin(x);
}

App::App() {
    running = false;
    bg_color = BG_COLOR;
    int rendererFlags = SDL_RENDERER_ACCELERATED;
    int windowFlags = 0;

    width = WIDTH;
    height = HEIGHT;

    renderer = (Renderer*)calloc(1, sizeof(Renderer));

    renderer->window = SDL_CreateWindow("Patcher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer->renderer = SDL_CreateRenderer(renderer->window, -1, rendererFlags);

    small_plot = Plot({small_range_rect, small_screen_rect}, function_to_draw);
    big_plot   = Plot({big_range_rect,   big_screen_rect  }, function_to_draw);


}

App::~App() {
    big_plot.~Plot();
    small_plot.~Plot();
    SDL_DestroyRenderer(renderer->renderer);
    SDL_DestroyWindow(renderer->window);
    free(renderer);
    return;
}

void App::run() {
    running = true;
    SDL_SetRenderTarget(renderer->renderer, NULL);
    SDL_Event event;
    Vector vector1(5, 0, 0.04);
    Pointf point1 = {0, 0};
    Vector vector2(4, 0, 0.04);
    Pointf point2 = {0, 1};
    while (running) {
        clock_t t = clock();
        while (SDL_PollEvent(&event)) {
            parseEvent(event);
        }
        
        vector1.update();
        vector2.update();

        SDL_SetRenderDrawColor(renderer->renderer, OPEN_RGBA(bg_color));
        SDL_RenderClear(renderer->renderer);
        small_plot.render(renderer);
        big_plot.render(renderer);

        big_plot.renderVector(renderer, vector1, point1);
        small_plot.renderVector(renderer, vector2, point2);

        SDL_RenderPresent(renderer->renderer);
        printf("%lf\n", CLOCKS_PER_SEC / ((double)(clock() - t)));
        SDL_Delay(10);
    }
}

void App::parseEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        running = false;
    }
}