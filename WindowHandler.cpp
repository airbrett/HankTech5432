#include "WindowHandler.h"

WindowHandler::WindowHandler(const size_t W, const size_t H)
{
	SDL_Init(SDL_INIT_VIDEO);
	mWnd = SDL_CreateWindow("Do what now?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_OPENGL);

	std::fill(std::begin(mKeys), std::end(mKeys), 0);
	std::fill(std::begin(mButtons), std::end(mButtons), 0);
}

void WindowHandler::Update()
{
	SDL_PumpEvents();

	if (SDL_GetKeyboardFocus() == mWnd)
	{
		const Uint8* state = SDL_GetKeyboardState(nullptr);

		mKeys['w'] = state[SDL_SCANCODE_W];
		mKeys['s'] = state[SDL_SCANCODE_S];
		mKeys['a'] = state[SDL_SCANCODE_A];
		mKeys['d'] = state[SDL_SCANCODE_D];
		mKeys[27] = state[SDL_SCANCODE_ESCAPE];
	}

	if (SDL_GetMouseFocus() == mWnd)
	{
		const Uint32 State = SDL_GetMouseState(&mMouseX, &mMouseY);

		mButtons[0] = State & SDL_BUTTON(1);
		mButtons[1] = State & SDL_BUTTON(2);
		mButtons[2] = State & SDL_BUTTON(3);
	}
}

SDL_Window* WindowHandler::GetHandle()
{
	return mWnd;
}

int WindowHandler::Width()
{
	int W;
	SDL_GetWindowSize(mWnd, &W, nullptr);

	return W;
}

int WindowHandler::Height()
{
	int H;
	SDL_GetWindowSize(mWnd, nullptr, &H);

	return H;
}

void WindowHandler::Swap()
{
	SDL_GL_SwapWindow(mWnd);
}

bool WindowHandler::KeyDown(const uint8_t AsciiCode)
{
	return mKeys[AsciiCode] != 0;
}

int WindowHandler::MouseX()
{
	return mMouseX;
}

int WindowHandler::MouseY()
{
	return mMouseY;
}

void WindowHandler::MouseSetPos(const int32_t X, const int32_t Y)
{
	if (SDL_GetMouseFocus() == mWnd)
		SDL_WarpMouseInWindow(mWnd, X, Y);
}

bool WindowHandler::ButtonDown(const int Button)
{
	return mButtons[Button] != 0;
}
