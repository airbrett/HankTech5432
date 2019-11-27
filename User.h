#pragma once
#include <array>

class User
{
private:
	
	std::array<uint8_t, 255>* mKeys;

public:
	User(std::array<uint8_t, 255>* Keys);
	void Update();
};
