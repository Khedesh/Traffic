#ifndef SDLGUI_H
#define SDLGUI_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include "filereader.h"

class SDLGui
{
	SDL_Surface* screen;

	int width;
	int height;

	float cur_time;

	float step;
	FileReader* reader;

	public:

	SDLGui(int w = 800, int h = 600);
	~SDLGui();

	void initialize(int w, int h);

	bool handle_event();

	bool update();
};

#endif // SDLGUI_H
