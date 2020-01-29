#pragma once
#include <glm/glm.hpp>

class Thing;
class GraphicsHandle;

class GraphicsComponent
{
	friend class Context;

private:
	Thing* mThing;
	float* mBuffer;
	unsigned int mNumVerticies;
	//Someday
	//GLuint mVBO;
	//GLuint mIBO;

public:
	GraphicsComponent(Thing* T);

	void SetModel();
};
