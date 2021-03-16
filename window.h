#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "text.h"

class Window {
	public:
		Window();
		~Window();

		SDL_Renderer* get_render();
		void create_window();

		SDL_Window* window;
		SDL_Renderer* renderer;
};

#endif