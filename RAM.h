#pragma once
#include "Thing.h"

#include <memory>
#include <vector>

class RAM
{
private:
	std::vector<std::shared_ptr<Thing>> mObjects;

public:
	RAM();

	template<typename T>
	std::shared_ptr<T> Rez()
	{
		std::shared_ptr<T> Obj = std::make_shared<T>();
		
		mObjects.push_back(Obj); 

		return Obj;
	}

	std::vector<std::shared_ptr<Thing>> GetObjects();
};
