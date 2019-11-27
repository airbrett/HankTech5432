#pragma once
#include "Instance.h"

class Player : public Thing
{
private:
	Instance* mInst;

public:
	Player();

	void Init(Instance* Inst);

	virtual void Update(const float dt);
};
