#pragma once
#include "Thing.h"
#include "Instance.h"

#include <SDL.h>

#include <vector>

class Draw
{
private:
	Instance* mInst;
	std::vector<Thing*>* mThings;
	SDL_Window* mWnd;
	SDL_GLContext mCtx;

public:
	Draw(Instance* Inst);
	void Init();
	void Update();
};
