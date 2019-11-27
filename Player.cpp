#include "Player.h"

Player::Player()
{
	Draw = false;
}

void Player::Init(Instance* Inst)
{
	mInst = Inst;
}

void Player::Update(const float dt)
{
	const float SPD = 0.15f;

	if (mInst->Keys['w'])
		Move({ 0,0,SPD*dt });
	if (mInst->Keys['s'])
		Move({ 0,0,-SPD*dt });

	if (mInst->Keys['a'])
		Move({ SPD*dt,0,0 });
	if (mInst->Keys['d'])
		Move({ -SPD*dt,0,0 });

	if (mInst->Keys['q'])
		Turn({ 0,SPD*dt,0.0f });
	if (mInst->Keys['e'])
		Turn({ 0,-SPD*dt,0.0f });
}
