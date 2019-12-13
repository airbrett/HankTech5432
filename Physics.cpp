#include "Physics.h"

struct PhysicsInfo
{
	b2Body* Body;
};

Physics::Physics(std::vector<Thing*>* Things) :
	mThings(Things)
{
	b2Vec2 gravity(0.0f, 0.0f);

	mWorld = new b2World(gravity);
}

void Physics::Update(const float dt)
{
	mWorld->Step(dt, 8, 3);

	Thing* Thg;

	for (b2Body* Body = mWorld->GetBodyList(); Body != nullptr; Body = Body->GetNext())
	{
		if (Body->IsAwake())
		{
			const b2Vec2& Pos = Body->GetPosition();
			Thg = reinterpret_cast<Thing*>(Body->GetUserData());

			Thg->SetPos(Pos.x, Thg->GetPos().y, Pos.y);
		}
	}
}

void Physics::AddThingSquare(Thing* Thg, const float w, const float h, const float d)
{
	b2FixtureDef FixDef;
	b2BodyDef BodyDef;
	b2PolygonShape Shape;
	
	BodyDef.position.Set(w/2, h/2);

	b2Body* Body = mWorld->CreateBody(&BodyDef);
	

	Shape.SetAsBox(w, h);

	FixDef.shape = &Shape;
	FixDef.density = d;

	b2Fixture* Fixture = Body->CreateFixture(&FixDef);

	//Fixture->SetUserData(Thg);
	Body->SetUserData(Thg);

	Thg->SetPhysicsHandle(Body);
}

void Physics::AddThingCircle(Thing* Thg, const float r, const float d)
{
	b2BodyDef BodyDef;
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(0.0f, 0.0f);
	BodyDef.linearDamping = 0.5f;
	BodyDef.angularDamping = 0.5f;
	//BodyDef.fixedRotation = true;

	b2Body* Body = mWorld->CreateBody(&BodyDef);

	b2CircleShape Shape;
	Shape.m_radius = r;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Shape;
	fixtureDef.density = d;
	fixtureDef.friction = 0.3f;
	

	b2Fixture* Fixture = Body->CreateFixture(&fixtureDef);

	Body->SetUserData(Thg);

	Thg->SetPhysicsHandle(Body);
}


void Physics::SetThingPos(Thing* Thg, const float x, const float z)
{
	b2Body* Body = reinterpret_cast<b2Body*>(Thg->GetPhysicsHandle());

	Body->SetTransform({ x, z }, Body->GetAngle());
}

void Physics::ApplyThingForce(Thing* Thg, const float x, const float z)
{
	b2Body* Body = reinterpret_cast<b2Body*>(Thg->GetPhysicsHandle());

	//Body->ApplyForceToCenter({ x, z }, true);
	//Body->ApplyLinearImpulseToCenter({ x,z }, true);
	Body->SetLinearVelocity({ x,z });
}
