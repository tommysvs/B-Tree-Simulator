#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "window.h"
#include "graphics.h"

class Text {
	private:
		SDL_Surface* surface;
		SDL_Texture* texture;
		TTF_Font* font;
		SDL_Rect rect;
	public:
		void set_text(std::string, int, SDL_Renderer*);
};

#endif

