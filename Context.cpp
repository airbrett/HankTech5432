#include "Context.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl/glew.h>

Context::Context(std::shared_ptr<WindowHandler> Window) :
	mWnd(Window)
{
	mCtx = SDL_GL_CreateContext(Window->GetHandle());

	SDL_GL_SetSwapInterval(1);

	glewInit();

	Init();
}

void Context::Init()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
}

size_t Context::CreateTexture(const uint8_t* const Bytes, const std::size_t Len, const std::size_t Width, const std::size_t Height)
{
	GLuint Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(Width), static_cast<GLsizei>(Height), 0, GL_RGBA, GL_UNSIGNED_BYTE, Bytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	size_t Handle;
	if (mTexHandMan.Rez(Handle))
		mResources.push_back(Texture);
	else
		mResources[Handle] = Texture;

	return Handle;
}

std::size_t Context::CreateVertexBuffer(const Vertex* Verticies, const std::size_t Count)
{
	GLuint VBO;
	std::size_t Handle;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Count, Verticies, GL_STATIC_DRAW);

	if (mTexHandMan.Rez(Handle))
		mResources.push_back(VBO);
	else
		mResources[Handle] = VBO;

	return Handle;
}

std::size_t Context::CreateIndexBuffer(const unsigned int* Indices, const std::size_t Count)
{
	GLuint IBO;
	size_t Handle;

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Count, Indices, GL_STATIC_DRAW);

	if (mTexHandMan.Rez(Handle))
		mResources.push_back(IBO);
	else
		mResources[Handle] = IBO;

	return Handle;
}

void Context::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::SetProj(const glm::mat4& Proj)
{
	if (mMtxMode != GL_PROJECTION)
	{
		mMtxMode = GL_PROJECTION;
		glMatrixMode(GL_PROJECTION);
	}

	glLoadMatrixf(glm::value_ptr(Proj));
}

void Context::SetModelView(const glm::mat4& View)
{
	if (mMtxMode != GL_MODELVIEW)
	{
		mMtxMode = GL_MODELVIEW;
		glMatrixMode(GL_MODELVIEW);
	}

	glLoadMatrixf(glm::value_ptr(View));
}

void Context::SetVertexBuffer(const std::size_t Buff)
{
	glBindBuffer(GL_ARRAY_BUFFER, mResources[Buff]);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(sizeof(Vertex::Pos)));
}

void Context::SetIndexBuffer(const std::size_t Buff)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mResources[Buff]);
}

void Context::SetTex(const std::size_t Tex)
{
	glBindTexture(GL_TEXTURE_2D, mResources[Tex]);
}

void Context::Submit(const std::size_t Count)
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Count), GL_UNSIGNED_INT, nullptr);
}
