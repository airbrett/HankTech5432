#pragma once
#include "Thing.h"
#include "HandleHandler.h"

#include <Box2D/Box2D.h>

#include <glm/glm.hpp>

#include <vector>

class Physics
{
private:
	b2World* mWorld;
	HandleHandler mHandle;
	std::vector<b2Body*> mBodies;
	HandleHandler mBodyHandMan;

public:
	Physics();

	void Update(const double dt);
	//void AddThingSquare(Thing* Thg, const float w, const float h, const float d);
	//void AddThingCircle(Thing* Thg, const float r, const float d);

	std::size_t CreateSquare(const float w, const float h, const float d);
	std::size_t CreateCircle(const float r, const float d);
	bool GetPos(const std::size_t Body, glm::vec3& Out);

	void SetPosition(const std::size_t Handle, const glm::vec3& Pos);
	void ApplyForce(const std::size_t Handle, const glm::vec3& Force);
	void SetLinearVelocity(const std::size_t Handle, const glm::vec3& Velocity);
	void SetMass(const std::size_t Handle, const float Mass);
};

