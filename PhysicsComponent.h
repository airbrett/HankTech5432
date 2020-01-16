#pragma once

#include <glm/glm.hpp>

class Thing;
class Phyiscs;
class b2Body;
class b2World;

class PhysicsComponent
{
	friend class Physics;

private:
	Thing* mThing;
	b2World* mWorld;
	b2Body* mBody;
	float mMass;

	PhysicsComponent(Thing* Owner, b2World* World);

public:
	const static size_t CIRCLE = 0;
	const static size_t SQUARE = 1;

	Thing* GetThing();

	void SetShape(const size_t Shape, const float Size);
	void SetMass(const float Mass);
	
	void SetPosition(const glm::vec3& Pos);
	void ApplyForce(const glm::vec3& Force);
	void SetLinearVelocity(const glm::vec3& Velocity);
};
