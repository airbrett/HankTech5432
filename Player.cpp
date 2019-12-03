#include "Player.h"

Player::Player()
{
	Draw = false;
}

void Player::Init(std::shared_ptr<WindowHandler>& Inst)
{
	mWnd = Inst;

	MouseX = mWnd->MouseX();
	MouseY = mWnd->MouseY();
}

void Player::Update(const float dt)
{
	const float SPD = 0.15f;

	if (mWnd->KeyDown('w'))
		Move({ 0,0,SPD*dt });
	if (mWnd->KeyDown('s'))
		Move({ 0,0,-SPD*dt });

	if (mWnd->KeyDown('a'))
		Move({ SPD*dt,0,0 });
	if (mWnd->KeyDown('d'))
		Move({ -SPD*dt,0,0 });


	const int32_t Mx = mWnd->Width() / 2 - mWnd->MouseX();
	const int32_t My = mWnd->MouseY() - mWnd->Height() / 2;

	Turn({ 0,Mx*0.1f*dt,0.0f });
	Turn({ My*0.1f*dt,0.0f,0.0f });

	mWnd->MouseSetPos(mWnd->Width() / 2, mWnd->Height() / 2);
}
