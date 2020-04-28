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
		mResources[Handle] = Texture;
	else
		mResources.push_back(Texture); 

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
		mResources[Handle] = VBO;
	else
		mResources.push_back(VBO); 

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
		mResources[Handle] = IBO;
	else
		mResources.push_back(IBO); 

	return Handle;
}

std::size_t Context::CreateProgram(const std::string& Source)
{
	static const char* DIVIDER = "[VTX^^^FRAGvvv]";
	static const std::size_t DIVIDER_LEN = std::strlen(DIVIDER);

	const std::size_t DividerIndex = Source.find(DIVIDER);

	const GLint ProgramLen[] = { static_cast<GLint>(DividerIndex), static_cast<GLint>(Source.size() - (DividerIndex + DIVIDER_LEN)) };
	const char* ProgramSrc[] = { Source.c_str(), Source.c_str() + DividerIndex + DIVIDER_LEN };

	std::size_t Handle;

	//Compile vertex shader
	GLuint Vtx = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vtx, 1, &ProgramSrc[0], &ProgramLen[0]);
	glCompileShader(Vtx);

	CheckShader(Vtx);

	//Compile fragment shader
	GLuint Frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Frag, 1, &ProgramSrc[1], &ProgramLen[1]);
	glCompileShader(Frag);

	CheckShader(Frag);

	//Create shader program
	ShaderProgram Program;

	Program.Program = glCreateProgram();

	glAttachShader(Program.Program, Frag);
	glAttachShader(Program.Program, Vtx);

	//Link shader program
	glLinkProgram(Program.Program);

	CheckShaderProgram(Program.Program);

	//Maybe this and all its related parts should exist outside of this class...
	Program.APos = glGetAttribLocation(Program.Program, "a_pos");
	Program.ACoord0 = glGetAttribLocation(Program.Program, "a_coord0");
	Program.UMvp = glGetUniformLocation(Program.Program, "u_mvp");

	glUseProgram(Program.Program);

	glEnableVertexAttribArray(Program.APos);
	glEnableVertexAttribArray(Program.ACoord0);

	if (mProgramHandlePool.Rez(Handle))
		mPrograms[Handle] = Program;
	else
		mPrograms.push_back(Program);

	return Handle;
}

void Context::CheckShader(GLuint Shader)
{
	GLint Status;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &Status);

	if (Status == GL_FALSE)
	{
		GLint ErrorLen = 0;
		GLsizei slen = 0;

		glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &ErrorLen);

		if (ErrorLen > 1)
		{
			std::string CompileLog;
			CompileLog.resize(ErrorLen);
			glGetShaderInfoLog(Shader, ErrorLen, &slen, &CompileLog[0]);
			throw std::runtime_error(CompileLog);
		}
	}
}

void Context::CheckShaderProgram(GLuint ShaderProgram)
{
	GLint LinkStatus;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &LinkStatus);

	if (LinkStatus == GL_FALSE)
	{
		GLint ErrorLen = 0;

		glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &ErrorLen);

		if (ErrorLen > 1)
		{
			std::string CompileLog;
			GLsizei slen = 0;

			CompileLog.resize(ErrorLen);

			glGetProgramInfoLog(ShaderProgram, ErrorLen, &slen, &CompileLog[0]);
			throw std::runtime_error(CompileLog);
		}
	}
}

std::size_t Context::CreateAttibute(const std::size_t Program, const std::string& Name)
{
	std::size_t Handle;

	GLint Loc = glGetAttribLocation(mResources[Program], Name.c_str());

	if (mTexHandMan.Rez(Handle))
		mResources[Handle] = Loc;
	else
		mResources.push_back(Loc);

	return Handle;
}

std::size_t Context::CreateUniform(const std::size_t Program, const std::string& Name)
{
	std::size_t Handle;

	GLint Loc = glGetUniformLocation(mResources[Program], Name.c_str());

	if (mTexHandMan.Rez(Handle))
		mResources[Handle] = Loc;
	else
		mResources.push_back(Loc);

	return Handle;
}

void Context::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Context::SetProj(const glm::mat4& Proj)
{
	mProj = Proj;
}

void Context::SetModelView(const glm::mat4& View)
{
	glUniformMatrix4fv(mPrograms[mProgram].UMvp, 1, GL_FALSE, glm::value_ptr(mProj * View));
}

void Context::SetVertexBuffer(const std::size_t Buff)
{
	glBindBuffer(GL_ARRAY_BUFFER, mResources[Buff]);

	glVertexAttribPointer(mPrograms[mProgram].APos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(mPrograms[mProgram].ACoord0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(Vertex::Pos)));
}

void Context::SetIndexBuffer(const std::size_t Buff)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mResources[Buff]);
}

void Context::SetTex(const std::size_t Tex)
{
	glBindTexture(GL_TEXTURE_2D, mResources[Tex]);
}

void Context::SetProgram(const std::size_t Program)
{
	ShaderProgram& Prog = mPrograms[Program];

	mProgram = Program;

	glUseProgram(Prog.Program);
}

void Context::SetUniformMat4(const std::size_t Uniform, const glm::mat4& Mat)
{
	glUniformMatrix4fv(mPrograms[mProgram].UMvp, 1, GL_FALSE, glm::value_ptr(Mat));
}

void Context::Submit(const std::size_t Count)
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Count), GL_UNSIGNED_INT, nullptr);
}
