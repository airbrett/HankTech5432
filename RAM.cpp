#include "RAM.h"

RAM::RAM()
{
}

std::vector<std::shared_ptr<Thing>> RAM::GetObjects()
{
	return mObjects;
}
