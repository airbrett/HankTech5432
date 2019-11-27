#pragma once
#include "Thing.h"

#include <vector>

class Physics
{
private:
	std::vector<Thing*>* mThings;

public:
	Physics(std::vector<Thing*>* Things);
	void Update();
};
