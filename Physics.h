#pragma once
#include "Thing.h"
#include "HandleHandler.h"
#include "Instance.h"
#include "PhysicsComponent.h"

#include <Box2D/Box2D.h>

#include <glm/glm.hpp>

#include <vector>

class Physics
{
private:
	const float UPDATE_STEP;
	b2World* mWorld;
	HandleHandler mHandle;
	double mPhysicsTime;
	std::shared_ptr<Instance> mInst;

public:
	Physics(std::shared_ptr<Instance>& Inst, std::vector<Thing*>* Things);

	PhysicsComponent* CreateComponent(Thing* T);

	void Update();
	void AddThingSquare(Thing* Thg, const float w, const float h, const float d);
	void AddThingCircle(Thing* Thg, const float r, const float d);
};

