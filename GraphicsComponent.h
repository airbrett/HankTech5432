#pragma once
#include <glm/glm.hpp>

#include <vector>

class Thing;
class GraphicsHandle;

class GraphicsComponent
{
	friend class Context;

private:
	struct Vertex
	{
		glm::vec3 Pos;
		glm::vec2 TexCoord;
	};

	Thing* mThing;
	std::vector<unsigned int> mIndicies;
	std::vector<Vertex> mVtx;
	size_t mTex;
	//Someday
	//GLuint mVBO;
	//GLuint mIBO;

public:
	GraphicsComponent(Thing* T);

	void SetModel(const char* Path);
};
