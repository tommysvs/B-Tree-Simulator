#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

class Graphics {
	private:
		SDL_Texture* texture;
		SDL_Rect rect;
	public:
		void set_texture(SDL_Texture*);
		void set_rect(SDL_Rect);
		void set_rect(SDL_Renderer*, SDL_Rect);
		void set_pos(int, int);
		void set_size(int, int);

		SDL_Rect get_rect();
		int get_x();
		int get_y();
		int get_w();
		int get_h();
};

#endif



