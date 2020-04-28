#pragma once
#include "WindowHandler.h"
#include "HandleHandler.h"

#include <gl/glew.h>

#include <glm/glm.hpp>

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
	struct ShaderProgram
	{
		GLint Program;
		GLint APos;
		GLint ACoord0;
		GLint UMvp;
	};

	std::shared_ptr<WindowHandler> mWnd;
	SDL_GLContext mCtx;
	HandleHandler mTexHandMan;
	HandleHandler mProgramHandlePool;
	std::vector<GLuint> mResources;
	std::vector<ShaderProgram> mPrograms;
	unsigned int mMtxMode;
	std::size_t mProgram;
	glm::mat4 mProj;

	void CheckShader(GLuint Shader);
	void CheckShaderProgram(GLuint ShaderProgram);

public:
	Context(std::shared_ptr<WindowHandler> Window);
	void Init();

	std::size_t CreateVertexBuffer(const Vertex* Verticies, const std::size_t Count);
	std::size_t CreateIndexBuffer(const unsigned int* Indices, const std::size_t Count);
	std::size_t CreateTexture(const uint8_t* const Bytes, const std::size_t Len, const std::size_t Width, const std::size_t Height);
	std::size_t CreateProgram(const std::string& Source);
	std::size_t CreateAttibute(const std::size_t Program, const std::string& Name);
	std::size_t CreateUniform(const std::size_t Program, const std::string& Name);

	void Clear();
	void SetProj(const glm::mat4& Proj);
	void SetModelView(const glm::mat4& View);
	void SetVertexBuffer(const std::size_t Buff);
	void SetIndexBuffer(const std::size_t Buff);
	void SetTex(const std::size_t Tex);
	void SetProgram(const std::size_t Program);
	void SetUniformMat4(const std::size_t Uniform, const glm::mat4& Mat);
	void Submit(const std::size_t Count);
};
