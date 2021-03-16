#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "window.h"
#include "graphics.h"

class Text : Graphics {
	private:
		TTF_Font* font;
		std::string text;
	public:
		void set_text(std::string, int, SDL_Renderer*);
};

#endif

