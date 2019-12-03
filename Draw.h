#pragma once
#include "Thing.h"
#include "WindowHandler.h"

#include <memory>
#include <vector>

class Draw
{
private:
	std::vector<Thing*>* mThings;
	SDL_GLContext mCtx;


public:
	Draw(std::shared_ptr<WindowHandler> Window);
	void Init();
	void Update(Thing* Camera, std::vector<Thing*>* Things);
};
