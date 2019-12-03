#pragma once
#include "Thing.h"

#include <Box2D/Box2D.h>

#include <vector>

class Physics
{
private:
	std::vector<Thing*>* mThings;
	b2World* mWorld;

public:
	Physics(std::vector<Thing*>* Things);

	void Update(const float dt);
	b2Body* AddCube(const int x, const int y, void* Data);
	b2Body* AddCharacter(const float x, const float y);

};
