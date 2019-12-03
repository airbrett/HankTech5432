#pragma once
#include "Thing.h"
#include "WindowHandler.h"

#include <array>
#include <memory>
#include <vector>

class Draw;

struct Instance
{
	std::vector<Thing*> Things;
	std::array<uint8_t, 255> Keys;
	std::shared_ptr<WindowHandler> Window;
	
	Thing* Camera;
};
