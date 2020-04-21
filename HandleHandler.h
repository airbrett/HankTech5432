#pragma once
#include <queue>

class HandleHandler
{
private:
	std::size_t mMaxIndex;
	std::queue<size_t> mDerezed;

public:
	HandleHandler();

	bool Rez(std::size_t& Index);
	void Derez(const std::size_t Index);
};
