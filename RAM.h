#pragma once
#include "Thing.h"

#include <vector>

class RAM
{
private:
	std::vector<Thing*>* mThings;
	std::vector<Thing*> mRezed;
	std::vector<size_t> mDeRez;

public:
	RAM(std::vector<Thing*>* Things);
	void DeRez(size_t Index);
	

	template<typename T>
	T* Rez()
	{
		T* ThingRez = new T;
		
		mRezed.emplace_back(ThingRez);

		return ThingRez;
	}

	void Update();
};
