#pragma once
#include "Thing.h"
#include "WindowHandler.h"

#include <memory>

class Player : public Thing
{
private:
	std::shared_ptr<WindowHandler> mWnd;
	int32_t MouseX;
	int32_t MouseY;

public:
	Player();

	void Init(std::shared_ptr<WindowHandler>& Wnd);

	virtual void Update(const float dt);
};
