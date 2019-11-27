#include "RAM.h"

#include <algorithm>

RAM::RAM(std::vector<Thing*>* Things) :
	mThings(Things)
{
}

void RAM::DeRez(size_t Index)
{
	mDeRez.emplace_back(Index);
}

void RAM::Update()
{
	if (!mDeRez.empty())
	{
		std::sort(std::begin(mDeRez), std::end(mDeRez), std::isgreater<size_t, size_t>);

		for (size_t i : mDeRez)
			mThings->erase(std::begin(*mThings) + i);

		mDeRez.clear();
	}

	if (!mRezed.empty())
	{
		for (Thing* T : mRezed)
			mThings->emplace_back(T);

		mRezed.clear();
	}
}
