#include "text.h"

void Text::set_text(std::string _text, int _size, SDL_Renderer* _renderer) {
	SDL_Color color = { 26, 97, 33, 255};
	font = TTF_OpenFont("font.ttf", _size);
	const char* text = _text.c_str();

	surface = TTF_RenderText_Solid(font, text, color);
	texture = SDL_CreateTextureFromSurface(_renderer, surface);

	rect = { 20, 20, surface->w, surface->h };

	SDL_RenderCopy(_renderer, texture, NULL, &rect);
}