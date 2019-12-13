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
	void AddThingSquare(Thing* Thg, const float w, const float h, const float d);
	void AddThingCircle(Thing* Thg, const float r, const float d);
	void SetThingPos(Thing* Thg, const float x, const float z);
	void ApplyThingForce(Thing* Thg, const float x, const float z);
};
