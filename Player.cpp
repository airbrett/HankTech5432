#include "Player.h"

Player::Player()
{
	Draw = false;
}

void Player::Init(std::shared_ptr<WindowHandler>& Wnd, std::shared_ptr<Physics>& Phy)
{
	mWnd = Wnd;
	mPhy = Phy;

	MouseX = mWnd->MouseX();
	MouseY = mWnd->MouseY();
}

void Player::Update(const double dt)
{
	const float SPD = 250.0f;
	glm::vec3 Dir(0);

	if (mWnd->KeyDown('w'))
		Dir.z = SPD*dt;
	if (mWnd->KeyDown('s'))
		Dir.z = -SPD*dt;

	if (mWnd->KeyDown('a'))
		Dir.x = SPD*dt;
	if (mWnd->KeyDown('d'))
		Dir.x = -SPD*dt;

	const glm::vec3 Force = TransformVector(Dir);

	//SetLinearVelocity(Force);
	//PhysComp->SetLinearVelocity(Force);
	mPhy->SetLinearVelocity(PhysicalHandle, Force);


	const int32_t Mx = mWnd->Width() / 2 - mWnd->MouseX();
	const int32_t My = mWnd->MouseY() - mWnd->Height() / 2;
	const float Ms = 1.5f;

	Turn({ 0,Mx*Ms*dt,0.0f });
	Turn({ My*Ms*dt,0.0f,0.0f });

	mWnd->MouseSetPos(mWnd->Width() / 2, mWnd->Height() / 2);
}
