#include "text.h"

void Text::set_text(std::string _text, int _size, SDL_Renderer* _renderer) {
	SDL_Color color = { 26, 97, 33, 255};
	font = TTF_OpenFont("fonts/louis.ttf", _size);
	text = _text;

	if (font) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture* _texture = SDL_CreateTextureFromSurface(_renderer, surface);
		SDL_Rect rect;
		rect.x = rect.y = 200;
		set_texture(_texture);
		set_rect(rect);
	}
	else {
		std::cout << "\nError: Failed to load font.\n";
	}
}