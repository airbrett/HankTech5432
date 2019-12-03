#include "Physics.h"


Physics::Physics(std::vector<Thing*>* Things) :
	mThings(Things)
{
	b2Vec2 gravity(0.0f, 0.0f);

	mWorld = new b2World(gravity);
}

void Physics::Update(const float dt)
{
	mWorld->Step(dt, 8, 3);
	/*
	for (Thing* T : *mThings)
	{
		//Move T
	}
	*/
}


b2Body* Physics::AddCube(const int x, const int y, void* Data)
{
	b2BodyDef BodyDef;
	BodyDef.position.Set(x + 0.5f, y + 0.5f);

	b2Body* Body = mWorld->CreateBody(&BodyDef);
	b2PolygonShape Shape;

	Shape.SetAsBox(0.5f, 0.5f);

	b2Fixture* Fixture = Body->CreateFixture(&Shape, 0.0f);

	Fixture->SetUserData(Data);

	return Body;
}

b2Body* Physics::AddCharacter(const float x, const float y)
{
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(0.0f, 4.0f);

	b2Body* Body = mWorld->CreateBody(&BodyDef);

	b2CircleShape Shape;
	Shape.m_radius = 0.25f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	b2Fixture* Fixture = Body->CreateFixture(&fixtureDef);

	//Body->ApplyForce()

	return Body;
}