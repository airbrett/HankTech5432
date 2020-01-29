#pragma once
#include "Thing.h"
#include "WindowHandler.h"
#include "HandleHandler.h"
#include "GraphicsComponent.h"

#include <gl/glew.h>

#include <memory>
#include <vector>

class Context
{
private:
	std::shared_ptr<WindowHandler> mWnd;
	std::vector<Thing*>* mThings;
	SDL_GLContext mCtx;
	HandleHandler mTexHandMan;
	std::vector<GLuint> mTextures;
	std::vector<GraphicsComponent*> mComponents;

public:
	Context(std::shared_ptr<WindowHandler> Window);
	void Init();
	void Update(Thing* Camera);

	size_t LoadTexture(const uint8_t* const Bytes, const size_t Len, const size_t Width, const size_t Height);

	GraphicsComponent* CreateComponent(Thing* T);
};
