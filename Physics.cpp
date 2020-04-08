#include "Physics.h"

struct PhysicsInfo
{
	b2Body* Body;
};

Physics::Physics(std::shared_ptr<Instance>& Inst, std::vector<Thing*>* Things) :
	UPDATE_STEP(1.0f/60.0f),
	mInst(Inst),
	mPhysicsTime(0.0)
{
	b2Vec2 gravity(0.0f, 0.0f);

	mWorld = new b2World(gravity);
}

void Physics::Update()
{
	while (mInst->Time.GetTime() > mPhysicsTime + UPDATE_STEP)
	{
		mPhysicsTime += UPDATE_STEP;
		mWorld->Step(UPDATE_STEP, 8, 3);
	}
}

std::size_t Physics::CreateSquare(const float w, const float h, const float d)
{
	b2FixtureDef FixDef;
	b2BodyDef BodyDef;
	b2PolygonShape Shape;
	std::size_t Handle;

	BodyDef.position.Set(w / 2, h / 2);

	b2Body* Body = mWorld->CreateBody(&BodyDef);

	Shape.SetAsBox(w, h);

	FixDef.shape = &Shape;
	FixDef.density = d;

	b2Fixture* Fixture = Body->CreateFixture(&FixDef);

	if (mBodyHandMan.Rez(Handle))
		mBodies.push_back(Body);
	else
		mBodies[Handle] = Body;

	return Handle;
}

std::size_t Physics::CreateCircle(const float r, const float d)
{
	std::size_t Handle;
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

	if (mBodyHandMan.Rez(Handle))
		mBodies.push_back(Body);
	else
		mBodies[Handle] = Body;

	return Handle;
}

bool Physics::GetPos(const std::size_t Body, glm::vec3& Out)
{
	b2Body* bod = mBodies[Body];

	if (bod->IsAwake())
	{
		const b2Vec2& Pos = bod->GetPosition();

		Out = { Pos.x, 0, Pos.y };

		return true;
	}

	return false;
}

void Physics::SetPosition(const std::size_t Handle, const glm::vec3& Pos)
{
	b2Body* Body = mBodies[Handle];
	Body->SetTransform({ Pos.x, Pos.z }, Body->GetAngle());
}

void Physics::ApplyForce(const std::size_t Handle, const glm::vec3& Force)
{
	b2Body* Body = mBodies[Handle];
	Body->ApplyForceToCenter({ Force.x, Force.z }, true);
}

void Physics::SetLinearVelocity(const std::size_t Handle, const glm::vec3& Velocity)
{
	b2Body* Body = mBodies[Handle];
	Body->SetLinearVelocity({ Velocity.x, Velocity.z });
}

void Physics::SetMass(const std::size_t Handle, const float Mass)
{
	b2Body* Body = mBodies[Handle];
	b2MassData Data;

	Body->GetMassData(&Data);

	Data.mass = Mass;
	Body->SetMassData(&Data);
}


/*
void Physics::SetThingPos(Thing* Thg, const float x, const float z)
{
	b2Body* Body = reinterpret_cast<b2Body*>(Thg->GetBody());

	Body->SetTransform({ x, z }, Body->GetAngle());
}

void Physics::ApplyThingForce(Thing* Thg, const float x, const float z)
{
	b2Body* Body = reinterpret_cast<b2Body*>(Thg->GetBody());

	//Body->ApplyForceToCenter({ x, z }, true);
	//Body->ApplyLinearImpulseToCenter({ x,z }, true);
	Body->SetLinearVelocity({ x,z });
}
*/
