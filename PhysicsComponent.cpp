#include "PhysicsComponent.h"

#include "Physics.h"

#include <Box2D/Box2D.h>

PhysicsComponent::PhysicsComponent(Thing* Owner, b2World* World) :
	mThing(Owner),
	mWorld(World),
	mBody(nullptr),
	mMass(0.0f)
{
}

Thing* PhysicsComponent::GetThing()
{
	return mThing;
}

void PhysicsComponent::SetShape(const size_t Shape, const float Size)
{
	if (Shape == CIRCLE)
	{
		b2BodyDef BodyDef;
		BodyDef.type = b2_dynamicBody;
		BodyDef.position.Set(0.0f, 0.0f);
		BodyDef.linearDamping = 0.5f;
		BodyDef.angularDamping = 0.5f;
		//BodyDef.fixedRotation = true;

		mBody = mWorld->CreateBody(&BodyDef);

		b2CircleShape Shape;
		Shape.m_radius = Size/2;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &Shape;
		fixtureDef.density = mMass;
		fixtureDef.friction = 0.3f;

		b2Fixture* Fixture = mBody->CreateFixture(&fixtureDef);

		mBody->SetUserData(this);
	}
	else if (Shape == SQUARE)
	{
		b2FixtureDef FixDef;
		b2BodyDef BodyDef;
		b2PolygonShape Shape;

		BodyDef.position.Set(Size / 2, Size / 2);

		mBody = mWorld->CreateBody(&BodyDef);


		Shape.SetAsBox(Size, Size);

		FixDef.shape = &Shape;
		FixDef.density = mMass;

		b2Fixture* Fixture = mBody->CreateFixture(&FixDef);

		mBody->SetUserData(this);
	}
}

void PhysicsComponent::SetMass(const float Mass)
{
	b2MassData Data;

	mBody->GetMassData(&Data);

	Data.mass = Mass;
	mBody->SetMassData(&Data);
}

void PhysicsComponent::SetPosition(const glm::vec3& Pos)
{
	mBody->SetTransform({ Pos.x, Pos.z }, mBody->GetAngle());
}

void PhysicsComponent::ApplyForce(const glm::vec3& Force)
{
	mBody->ApplyForceToCenter({ Force.x, Force.z }, true);
}

void PhysicsComponent::SetLinearVelocity(const glm::vec3& Velocity)
{
	mBody->SetLinearVelocity({ Velocity.x, Velocity.z });
}
