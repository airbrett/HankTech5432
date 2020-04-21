#include "HandleHandler.h"

HandleHandler::HandleHandler() :
	mMaxIndex(0)
{
}

bool HandleHandler::Rez(std::size_t& Index)
{
	if (mDerezed.empty())
	{
		Index = mMaxIndex;
		mMaxIndex++;
		return false;
	}
	else
	{
		Index = mDerezed.front();
		mDerezed.pop();
		return true;
	}
}

void HandleHandler::Derez(const std::size_t Index)
{
	mDerezed.push(Index);
}
