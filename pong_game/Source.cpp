#include <SDL.h>
#include <SDL_timer.h>
#include <iostream>
#include <string>
#include <SDL_ttf.h>

using namespace std;

int SCREEN_X = 1600;
int SCREEN_Y = 900;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		std::cout << "Error" << std::endl;

	SDL_Window* win = SDL_CreateWindow("Simulation Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_X, SCREEN_Y, 0);

	Uint32 renderflags = SDL_RENDERER_ACCELERATED;

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);

	SDL_Rect rect;
	rect.w = 50;
	rect.h = 50;
	rect.x = SCREEN_X / 2 - rect.w / 2;
	rect.y = SCREEN_Y / 2 - rect.h / 2;

	SDL_Rect racket1;
	racket1.w = 20;
	racket1.h = 150;
	racket1.x = SCREEN_X - 120;
	racket1.y = SCREEN_Y / 2 - rect.h / 2;

	SDL_Rect racket2;
	racket2.w = 20;
	racket2.h = 150;
	racket2.x = 100;
	racket2.y = SCREEN_Y / 2 - rect.h / 2;

	SDL_Rect fillet;
	fillet.w = 20;
	fillet.h = SCREEN_Y;
	fillet.x = SCREEN_X / 2 - fillet.w / 2;
	fillet.y = 0;

	bool close = false;
	int xspeed = 5;
	int yspeed = 5;
	int racketspeed;
	int score = 0;
	bool move = false;
	char* msg;

	//this opens a font style and sets a size
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color White = { 255, 255, 255 };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	while (!close) {
		SDL_RenderClear(renderer);

		string temp_str = to_string(score);
		char* msg = (char*)temp_str.c_str();
		cout << msg << "\n";

		//particle rect
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderFillRect(renderer, &racket1);
		SDL_RenderFillRect(renderer, &racket2);
		SDL_RenderFillRect(renderer, &fillet);

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

		// Don't forget to free your surface and texture
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		rect.x += xspeed;
		rect.y += yspeed;

		racket2.y = rect.y-rect.h/2;

		if (rect.x + rect.w > SCREEN_X) {
			xspeed = -xspeed;
		}
		else if (rect.x < racket2.x + racket2.w) {
			xspeed = -xspeed;
		}
		else if (rect.x + rect.w > racket1.x && rect.y >= racket1.y && rect.y <= racket1.y + racket1.h) {
			xspeed = -xspeed;
			score += 1;
		}

		if (rect.y + rect.h > SCREEN_Y) {
			yspeed = -yspeed;
		}
		else if (rect.y < 0) {
			yspeed = -yspeed;
		}

		if (move) {
			racket1.y += racketspeed;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					move = true;
					racketspeed = -10;
					break;
				case SDLK_DOWN:
					move = true;
					racketspeed = 10;
					break;
				}
			}
			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					move = false;
					break;
				case SDLK_DOWN:
					move = false;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000 / 120);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}