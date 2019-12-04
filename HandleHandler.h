#pragma once
#include <queue>

class HandleHandler
{
private:
	size_t mMaxIndex;
	std::queue<size_t> mDerezed;

public:
	HandleHandler();

	bool Rez(size_t& Index);
	void Derez(const size_t Index);
};
