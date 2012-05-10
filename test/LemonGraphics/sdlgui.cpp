#include "sdlgui.h"
using namespace std;

SDLGui::SDLGui(int w, int h)
{
	initialize(w, h);
	reader = new FileReader("test.log");
	reader->read();
	step = 1.0f;
}

 SDLGui::~SDLGui()
{
	SDL_Quit();
	SDL_FreeSurface(screen);
	delete reader;
}

void SDLGui::initialize(int w, int h)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE);
}

bool SDLGui::handle_event()
{
	bool ret = true;

	SDL_Event e1;

	if(SDL_PollEvent(&e1))
	{
		if(e1.type == SDL_QUIT)
			ret = false;
		else if(e1.type == SDL_KEYDOWN)
		{
			unsigned char key = e1.key.keysym.sym;

			if(key == 'q')
			{
				ret = false;
			}
		}
	}

	return ret;
}

bool SDLGui::update()
{
	bool ret = true;

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	ret = handle_event();

	// finding the index
	int index = 0;
	while(cur_time < reader->get_chunk(index).frame_time)
	{
		index ++;
	}

	Chunk ch = reader->get_chunk(index);
	cout << "Time: " << cur_time << endl;
	cout << "Car Count: " << ch.pairs.size() << endl;
	cout << "Index: " << index << endl;
	for(unsigned i = 0 ; i < ch.pairs.size() ; i ++)
	{
		Chunk::Pair p = ch.pairs[i];
		float dt = cur_time - reader->get_chunk(index).frame_time;
		filledCircleRGBA(screen, p.pos + p.vel * dt, 10, 3, 255, 255, 255, 255);
	}

	cur_time += step;

	SDL_Delay(1);
	SDL_Flip(screen);

	return ret;
}
