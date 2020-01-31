#pragma once
#include <glm/glm.hpp>

#include <boost/filesystem.hpp>

#include <vector>

class Thing;
class GraphicsHandle;
class Context;

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
	Context* mCtx;
	std::vector<unsigned int> mIndicies;
	std::vector<Vertex> mVtx;
	size_t mTex;
	//Someday
	//GLuint mVBO;
	//GLuint mIBO;

	void LoadMesh(const boost::filesystem::path& Path);
	void LoadTexture(const boost::filesystem::path& Path);

public:
	GraphicsComponent(Context* C, Thing* T);

	void SetModel(const boost::filesystem::path& Path);
};
