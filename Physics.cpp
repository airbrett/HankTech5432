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

		PhysicsComponent* Comp;

		for (b2Body* Body = mWorld->GetBodyList(); Body != nullptr; Body = Body->GetNext())
		{
			if (Body->IsAwake())
			{
				const b2Vec2& Pos = Body->GetPosition();
				Comp = reinterpret_cast<PhysicsComponent*>(Body->GetUserData());

				Comp->GetThing()->SetPos({ Pos.x, Comp->GetThing()->GetPos().y, Pos.y });
			}
		}
	}
}

PhysicsComponent* Physics::CreateComponent(Thing* T)
{
	return new PhysicsComponent(T, mWorld);
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

	Body->SetUserData(Thg);
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
