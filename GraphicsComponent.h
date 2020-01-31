#pragma once
#include <glm/glm.hpp>

#include <boost/filesystem.hpp>

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
	
	size_t mTex;
	size_t mVtx;
	size_t mIdx;
	size_t mIdxCount;

	void LoadMesh(const boost::filesystem::path& Path);
	void LoadTexture(const boost::filesystem::path& Path);

public:
	GraphicsComponent(Context* C, Thing* T);

	void SetModel(const boost::filesystem::path& Path);
};
