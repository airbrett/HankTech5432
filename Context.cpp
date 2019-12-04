#include "Context.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

Context::Context(std::shared_ptr<WindowHandler> Window) :
	mWnd(Window)
{
	mCtx = SDL_GL_CreateContext(Window->GetHandle());

	glewInit();

	Init();
}

void Context::Init()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, g_vertex_buffer_data);
	glEnable(GL_DEPTH_TEST);
}

void Context::Update(Thing* Camera, std::vector<Thing*>* Things)
{
	const glm::vec3 CameraLook = Camera->Transform({ 0.0f, 0.0f, 1.0f });
	const glm::vec3 CameraUp(0.0, 1.0, 0.0);

	const glm::mat4 Projection = glm::perspective(glm::radians(30.0f), static_cast<float>(mWnd->Width()) / mWnd->Height(), 0.1f, 1000.0f);
	const glm::mat4 View = glm::lookAt(Camera->GetPos(), CameraLook, CameraUp);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(Projection));
	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);

	for (Thing* T : *Things)
	{
		if (T->DoDraw())
		{
			glLoadMatrixf(glm::value_ptr(View * T->GetMatrix()));

			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		}
	}

	
}


size_t Context::LoadTexture(const uint8_t* const Bytes, const size_t Len, const size_t Width, const size_t Height)
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
		mTextures.push_back(Texture);
	else
		mTextures[Handle] = Texture;

	return Handle;
}
