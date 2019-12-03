#pragma once
#include "Thing.h"
#include "WindowHandler.h"

#include <memory>
#include <vector>

class Context
{
private:
	std::shared_ptr<WindowHandler> mWnd;
	std::vector<Thing*>* mThings;
	SDL_GLContext mCtx;

public:
	Context(std::shared_ptr<WindowHandler> Window);
	void Init();
	void Update(Thing* Camera, std::vector<Thing*>* Things);
};
