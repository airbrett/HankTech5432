#pragma once
#include <glm/glm.hpp>

#include <vector>

class Thing;
class GraphicsHandle;

class GraphicsComponent
{
	friend class Context;

private:
	Thing* mThing;
	float* mBuffer;
	unsigned int mNumVerticies;
	std::vector<float> mVerticies;
	//Someday
	//GLuint mVBO;
	//GLuint mIBO;

public:
	GraphicsComponent(Thing* T);

	void SetModel(const char* Path);
};
