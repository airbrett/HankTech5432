#pragma once
#include "Thing.h"
#include "HandleHandler.h"

#include <Box2D/Box2D.h>

#include <glm/glm.hpp>

#include <functional>
#include <vector>

class Physics : public b2ContactListener
{
private:
	b2World* mWorld;
	HandleHandler mHandle;
	std::vector<b2Body*> mBodies;
	HandleHandler mBodyHandMan;

	std::function<void(std::size_t, std::size_t)> mCallback;

public:
	Physics();

	void Update(const double dt);

	void BeginContact(b2Contact* contact);
	//void AddThingSquare(Thing* Thg, const float w, const float h, const float d);
	//void AddThingCircle(Thing* Thg, const float r, const float d);

	std::size_t CreateSquare(const float w, const float h, const float d, const std::size_t data);
	std::size_t CreateCircle(const float r, const float d, const std::size_t data);
	bool GetPos(const std::size_t Body, glm::vec3& Out);

	void SetPosition(const std::size_t Handle, const glm::vec3& Pos);
	void ApplyForce(const std::size_t Handle, const glm::vec3& Force);
	void SetLinearVelocity(const std::size_t Handle, const glm::vec3& Velocity);
	void SetMass(const std::size_t Handle, const float Mass);

	void SetCollisionHandler(const std::function<void(std::size_t, std::size_t)>& Func);
};

