#include "graphics.h"

void Graphics::set_rect(SDL_Rect _rect) {
	rect = _rect;
}

void Graphics::set_rect(SDL_Renderer* _renderer, SDL_Rect _rect) {
	rect = _rect;
	SDL_SetRenderDrawColor(_renderer, 66, 181, 78, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(_renderer, &rect);
}

void Graphics::set_pos(int _x, int _y) {
	rect.x = _x;
	rect.y = _y;
}

void Graphics::set_size(int _w, int _h) {
	rect.w = _w;
	rect.h = _h;
}

SDL_Rect Graphics::get_rect() {
	return rect;
}

int Graphics::get_x() {
	return rect.x;
}

int Graphics::get_y() {
	return rect.y;
}

int Graphics::get_w() {
	return rect.w;
}

int Graphics::get_h() {
	return rect.h;
}