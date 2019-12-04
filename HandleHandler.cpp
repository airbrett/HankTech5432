#include "HandleHandler.h"

HandleHandler::HandleHandler() :
	mMaxIndex(0)
{
}

bool HandleHandler::Rez(size_t& Index)
{
	if (mDerezed.empty())
	{
		Index = mMaxIndex;
		mMaxIndex++;
		return true;
	}
	else
	{
		Index = mDerezed.front();
		mDerezed.pop();
		return false;
	}
}

void HandleHandler::Derez(const size_t Index)
{
	mDerezed.push(Index);
}
