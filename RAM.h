#pragma once
#include "Thing.h"
#include "HandleHandler.h"

#include <memory>
#include <vector>

class RAM
{
private:
	std::vector<std::shared_ptr<Thing>> mObjects;
	HandleHandler mHandlePool;

public:
	RAM();

	template<typename T>
	std::shared_ptr<T> Rez()
	{
		std::size_t Index;
		std::shared_ptr<T> Obj = std::make_shared<T>();
		
		if (mHandlePool.Rez(Index))
			mObjects[Index];
		else
			mObjects.push_back(Obj); 

		Obj->SetID(Index);

		return Obj;
	}

	std::vector<std::shared_ptr<Thing>> GetObjects();
};
