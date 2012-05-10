#include "sdlgui.h"

int main(int argc, char* argv[])
{
	SDLGui gui(800, 600);

	bool running = true;

	while(running)
	{

		running = gui.update();
	}

	return 0;
}
