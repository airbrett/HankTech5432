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

void Context::Update()
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(mProj));
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//lol this was interesting but is it really worth the effort?
	//another thing to play with is to move all this command junk
	//into it's own class so this one can focus on just being opengl
	GLenum Mode = 0;
	std::size_t Vtx = std::numeric_limits<std::size_t>::max();
	std::size_t Idx = std::numeric_limits<std::size_t>::max();
	std::size_t Tex = std::numeric_limits<std::size_t>::max();

	while (!mCmds.empty())
	{
		switch (mCmds.front())
		{
		case Commands::SetProj:
			if (Mode != GL_PROJECTION)
			{
				Mode = GL_PROJECTION;
				glMatrixMode(GL_PROJECTION);
			}

			mCmds.pop();

			glLoadMatrixf(glm::value_ptr(mMtx[mCmds.front()]));

			mCmds.pop();
			break;

		case Commands::SetView:
			if (Mode != GL_MODELVIEW)
			{
				Mode = GL_MODELVIEW;
				glMatrixMode(GL_MODELVIEW);
			}

			mCmds.pop();

			glLoadMatrixf(glm::value_ptr(mMtx[mCmds.front()]));

			mCmds.pop();
			break;

		case Commands::SetVtx:
			mCmds.pop();

			if (Vtx != mCmds.front())
			{
				Vtx = mCmds.front();
				glBindBuffer(GL_ARRAY_BUFFER, mResources[Vtx]);
				glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
				glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(sizeof(Vertex::Pos)));
			}

			mCmds.pop();
			break;

		case Commands::SetIdx:
			mCmds.pop();

			if (Idx != mCmds.front())
			{
				Idx = mCmds.front();
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mResources[Idx]);
			}

			mCmds.pop();
			break;

		case Commands::SetTex:
			mCmds.pop();

			if (Tex != mCmds.front())
			{
				Tex = mCmds.front();
				glBindTexture(GL_TEXTURE_2D, mResources[Tex]);
			}

			mCmds.pop();
			break;
			
		case Commands::Draw:
			mCmds.pop();

			glDrawElements(GL_TRIANGLES, mCmds.front(), GL_UNSIGNED_INT, 0);
			mCmds.pop();

			break;
		};
	}
	
	mMtx.clear();
}


size_t Context::CreateTexture(const uint8_t* const Bytes, const size_t Len, const size_t Width, const size_t Height)
{
	GLuint Texture;
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Bytes);

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

void Context::SetProj(const glm::mat4& Proj)
{
	mProj = Proj;

	const std::size_t Index = mMtx.size();
	mMtx.emplace_back(Proj);

	mCmds.emplace(Commands::SetProj);
	mCmds.emplace(Index);
}

void Context::SetView(const glm::mat4& View)
{
	mView = View;

	const std::size_t Index = mMtx.size();
	mMtx.emplace_back(View);

	mCmds.emplace(Commands::SetView);
	mCmds.emplace(Index);
}

void Context::SetVertexBuffer(const std::size_t Buff)
{
	mCmds.emplace(Commands::SetVtx);
	mCmds.emplace(Buff);
}

void Context::SetIndexBuffer(const std::size_t Buff)
{
	mCmds.emplace(Commands::SetIdx);
	mCmds.emplace(Buff);
}

void Context::SetTex(const std::size_t Tex)
{
	mCmds.emplace(Commands::SetTex);
	mCmds.emplace(Tex);
}

void Context::Draw(const std::size_t Count)
{
	mCmds.emplace(Commands::Draw);
	mCmds.emplace(Count);
}

GraphicsComponent* Context::CreateComponent(Thing* T)
{
	GraphicsComponent* Comp = new GraphicsComponent(this, T);

	mComponents.emplace_back(Comp);

	return Comp;
}
