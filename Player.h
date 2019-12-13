#pragma once
#include "Thing.h"
#include "WindowHandler.h"
#include "Physics.h"

#include <memory>

class Player : public Thing
{
private:
	std::shared_ptr<WindowHandler> mWnd;
	std::shared_ptr<Physics> mPhy;
	int32_t MouseX;
	int32_t MouseY;

public:
	Player();

	void Init(std::shared_ptr<WindowHandler>& Wnd, std::shared_ptr<Physics>& Phy);

	virtual void Update(const float dt);
};
