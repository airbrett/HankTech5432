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

void Player::Update(const float dt)
{
	const float SPD = 0.015f;
	glm::vec3 Dir(0);

	if (mWnd->KeyDown('w'))
		//Move({ 0,0,SPD*dt });
		Dir.z = SPD*dt;
	if (mWnd->KeyDown('s'))
		//Move({ 0,0,-SPD*dt });
		Dir.z = -SPD*dt;
	//else
	//	Dir.z = 0.0f;

	if (mWnd->KeyDown('a'))
		//Move({ SPD*dt,0,0 });
		Dir.x = SPD*dt;
	if (mWnd->KeyDown('d'))
		//Move({ -SPD*dt,0,0 });
		Dir.x = -SPD*dt;
	//else
	//	Dir.x = 0.0f;

	if (Dir.x != 0 || Dir.z != 0)
	{
		const glm::vec3 Force = TransformVector(Dir);
		//const glm::vec3 Force = TransformVector({ 0.0,0.0,0.0 });

		mPhy->ApplyThingForce(this, Force.x, Force.z);
	}


	const int32_t Mx = mWnd->Width() / 2 - mWnd->MouseX();
	const int32_t My = mWnd->MouseY() - mWnd->Height() / 2;

	Turn({ 0,Mx*0.1f*dt,0.0f });
	Turn({ My*0.1f*dt,0.0f,0.0f });

	mWnd->MouseSetPos(mWnd->Width() / 2, mWnd->Height() / 2);
}
