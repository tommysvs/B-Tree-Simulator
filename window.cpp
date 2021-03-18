#include "window.h"

static bool running = true;

Window::Window() : window(NULL), renderer(NULL) { }

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Renderer* Window::get_render() {
	return renderer;
}

void Window::create_window() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "\nError: Failed to initialize SDL.\n";
		return;
    } else {
        Graphics graphic;
        Text text;
        
        window = SDL_CreateWindow("B-Tree Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_WINDOW_SHOWN);

        SDL_Surface* icon = IMG_Load("icon.png");
        SDL_SetWindowIcon(window, icon);

        if (window != 0) {
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_bool done = SDL_FALSE;

            TTF_Init();

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 156, 245, 165, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_Rect rect = { 500, 40, 200, 50 }; //x, y, w, h
                graphic.set_rect(renderer, rect);
                text.set_text("Lorem ipsum", 24, renderer);

                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer)
            SDL_DestroyRenderer(renderer);

        if (window)
            SDL_DestroyWindow(window);
    }

	if (window == nullptr) {
		std::cerr << "\nError: Failed to create window.\n";
		return;
	}
}