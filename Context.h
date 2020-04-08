#pragma once
#include "Thing.h"
#include "WindowHandler.h"
#include "HandleHandler.h"

#include <gl/glew.h>

#include <memory>
#include <queue>
#include <vector>

struct Vertex
{
	glm::vec3 Pos;
	glm::vec2 TexCoord;
};


class Context
{
private:
	std::shared_ptr<WindowHandler> mWnd;
	std::vector<Thing*>* mThings;
	SDL_GLContext mCtx;
	HandleHandler mTexHandMan;
	std::vector<GLuint> mResources;
	std::vector<GraphicsComponent*> mComponents;
	unsigned int mMtxMode;

public:
	Context(std::shared_ptr<WindowHandler> Window);
	void Init();

	std::size_t CreateVertexBuffer(const Vertex* Verticies, const std::size_t Count);
	std::size_t CreateIndexBuffer(const unsigned int* Indices, const std::size_t Count);
	size_t CreateTexture(const uint8_t* const Bytes, const size_t Len, const size_t Width, const size_t Height);

	void Clear();
	void SetProj(const glm::mat4& Proj);
	void SetModelView(const glm::mat4& View);
	void SetVertexBuffer(const std::size_t Buff);
	void SetIndexBuffer(const std::size_t Buff);
	void SetTex(const std::size_t Tex);
	void Submit(const std::size_t Count);
};
