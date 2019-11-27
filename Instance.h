#pragma once
#include "Thing.h"

#include <array>
#include <vector>

struct Instance
{
	std::vector<Thing*> Things;
	std::array<uint8_t, 255> Keys;
	Thing* Camera;
};
