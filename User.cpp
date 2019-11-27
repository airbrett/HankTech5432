#include "User.h"

#include <SDL.h>

//#include <algorithm>

User::User(std::array<uint8_t, 255>* Keys) :
	mKeys(Keys)
{

	std::fill(std::begin(*Keys), std::end(*Keys), 0);
}

void User::Update()
{
	SDL_Event E;

	while (SDL_PollEvent(&E))
	{
		switch (E.type)
		{
		case SDL_KEYDOWN:
			(*mKeys)[E.key.keysym.sym] = 1;
			break;
		case SDL_KEYUP:
			(*mKeys)[E.key.keysym.sym] = 0;
			break;
		}
	}
}
