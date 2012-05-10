#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

struct Car
{
	float pos;
	float vel;
};

typedef vector<Car> Road;

struct State
{
	float time;
	vector<Road> roads;
};

namespace
{
	vector<State> states;

	SDL_Surface* road_texture;
	SDL_Surface* red_car;

	int ox;
	int oy;

	const int foot_len = 40;
	bool enable_step = false;
}

void init()
{
	road_texture = IMG_Load("830.jpg"); 

	red_car = IMG_Load("surface2.gif");
}

void read_file(const char* file)
{
	/*ifstream fin(file, ios::in);

	State s;
	Road r;

	while(fin.good())
	{
		string line;

		fin >> line;

		if(line == "frame")
		{
			fin >> s.time;
		}
		else if(line == "road")
		{
			int index = 0;
			r.clear();
			fin >> index;
		}
		else if(line == "endroad")
		{
			s.roads.push_back(r);
		}
		else if(line == "car")
		{
			Car c;

			fin >> c.pos >> c.vel;

			r.push_back(c);
		}
		else if(line == "end")
		{
			states.push_back(s);
			s.roads.clear();
			r.clear();
		}
	}*/
	
	FILE* fptr = fopen(file, "r");

	int ret = 0;

	State s;
	Road r;

	while(!feof(fptr))
	{
		char line[80] = {0};

		ret = fscanf(fptr, "%s", line);

		if(strcmp(line, "frame") == 0)
		{
			ret = fscanf(fptr, "%f", &(s.time));
		}
		else if(strcmp(line, "road") == 0)
		{
			int index = 0;
			r.clear();
			ret = fscanf(fptr, "%d", &index);
		}
		else if(strcmp(line, "endroad") == 0)
		{
			s.roads.push_back(r);
		}
		else if(strcmp(line, "car") == 0)
		{
			Car c;

			ret = fscanf(fptr, "%f%f", &(c.pos), &(c.vel));

			r.push_back(c);
		}
		else if(strcmp(line, "end") == 0)
		{
			states.push_back(s);
			s.roads.clear();
			r.clear();
		}
	}
}

int main(int argc, char* argv[])
{
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Traffic 1.0.0", NULL);
	TTF_Font* font = TTF_OpenFont("FreeMono.ttf", 12);
	SDL_EnableKeyRepeat(1, 10);

	bool running = true;

	SDL_Event e1;

	float gtime = 0.0f;
	float step = 0.03f;
	init();
	char file[80] = {0};
	strcpy(file, "test.log");

	if(argc >= 2)
		read_file(argv[1]);
	for(unsigned i = 0 ; i < states.size() ; i ++)
	{
		//cout << "---------------------------------------" << endl;
		//cout << "State index: " << i << endl;
		//cout << "STime: " << states[i].time << endl;
		for(unsigned j = 0 ; j < states[i].roads.size() ; j ++)
		{
			//cout << "Road: " << j << endl;
			for(unsigned k = 0 ; k < states[i].roads[j].size() ; k ++)
			{
				Car c = states[i].roads[j][k];
				//cout << "Car: " << k << " " << c.pos << " " << c.vel << endl;
			}
		}
	}

	int index = 0;
	float last_time = 0;
	while(running)
	{
		cout << "=========================================" << endl;
		cout << "Time: " << gtime << endl;

		while(SDL_PollEvent(&e1))
		{
			if(e1.type == SDL_QUIT)
			{
				running = false;
			}
			else if(e1.type == SDL_KEYDOWN)
			{
				unsigned char key = e1.key.keysym.sym;

				if(key == 'q')
					running = false;
				else if(key == 'd')
				{
					ox += foot_len;
				}
				else if(key == 'a')
				{
					ox -= foot_len;
				}
				else if(key == SDLK_SPACE)
				{
					enable_step = !enable_step;
				}
				else if(key == 'f')
				{
					SDL_WM_ToggleFullScreen(screen);
				}
			}
		}

		//if(enable_step == true)
		//{
			// get the index
			if(gtime > states[index].time)
			{
				index ++;
			}
			else if(gtime <= states[index].time)
			{
				float dt = (SDL_GetTicks() - last_time) / 500;
				last_time = SDL_GetTicks();
				gtime += step;
				dt = 0;
			}
		//}
		cout << "State Index: " << index << endl;
		cout << "State Time: " << states[index].time << endl;

		// drawing
		float cur_time = states[index].time;
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		// road
		for(int i = 0 ; i < screen->w / road_texture->w + 1 ; i ++)
		{
			for(int j = 0 ; j < screen->h / road_texture->h + 1 ; j ++)
			{
				SDL_Rect rect;
				rect.w = road_texture->w;
				rect.h = road_texture->h;
				rect.x = i * road_texture->w;
				rect.y = j * road_texture->h;

				SDL_BlitSurface(road_texture, NULL, screen, &rect);
			}
		}

		// cars
		State cur_state = states[index];
		float scale = 32; // pixels per meter px/m
		boxRGBA(screen, 0, 0, screen->w, scale / 2, 50, 50, 255, 255);
		for(unsigned i = 0 ; i < cur_state.roads.size() ; i ++)
		{
			for(unsigned j = 0 ; j < cur_state.roads[i].size() ; j ++)
			{
				Car cur_car = cur_state.roads[i][j];
				//filledCircleRGBA(screen, cur_car.pos + cur_car.vel * (gtime - cur_time), 10, 3, 255, 255, 255, 255);
				pixelRGBA(screen, cur_car.pos + cur_car.vel * (gtime - cur_time), i, 100, 250, 250, 255);

				SDL_Rect rect;

				rect.w = red_car->w;
				rect.h = red_car->h;
				rect.x = scale * (cur_car.pos + cur_car.vel * (gtime - cur_time)) - ox;
				rect.y = scale * ((i * 2) + 1) - oy;

				// texture
				SDL_BlitSurface(red_car, NULL, screen, &rect);

				// text
				char buf[80] = {0};
				sprintf(buf, "v=%.3f", cur_car.vel);
				SDL_Color color;
				color.r = 50; color.g = 255; color.b = 150;
				SDL_Surface* text = TTF_RenderText_Blended(font, buf, color);

				SDL_BlitSurface(text, NULL, screen, &rect);
				SDL_FreeSurface(text);
			}
		}
		// line
		aalineRGBA(screen, ox / scale, 0, ox / scale, scale / 2, 200, 50, 50, 255);

		SDL_Delay(1);
		SDL_Flip(screen);


	}

	SDL_FreeSurface(road_texture);
	SDL_FreeSurface(red_car);
	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}
