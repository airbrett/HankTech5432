#pragma once
#include <glm/glm.hpp>

#include <boost/filesystem.hpp>

class Thing;
class GraphicsHandle;
class Context;

struct Vertex
{
	glm::vec3 Pos;
	glm::vec2 TexCoord;
};

class GraphicsComponent
{
	friend class Context;

private:
	
	Context* mCtx;

	void LoadMesh(const boost::filesystem::path& Path);
	void LoadTexture(const boost::filesystem::path& Path);

public:
	Thing* mThing;

	size_t mIdxCount;
	size_t mTex;
	size_t mVtx;
	size_t mIdx;

	GraphicsComponent(Context* C, Thing* T);

	void SetModel(const boost::filesystem::path& Path);
};
