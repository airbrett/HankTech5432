#include "Physics.h"


Physics::Physics(std::vector<Thing*>* Things) :
	mThings(Things)
{
}

void Physics::Update()
{
	for (Thing* T : *mThings)
	{
		//Move T
	}
}
