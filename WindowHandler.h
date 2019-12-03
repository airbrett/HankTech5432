#pragma once
#include <SDL.h>

#include <array>

class WindowHandler
{
private:
	SDL_Window* mWnd;
	std::array<uint8_t, 255> mKeys;
	int mMouseX;
	int mMouseY;
	std::array<uint8_t, 3> mButtons;

public:
	WindowHandler(const size_t W, const size_t H);

	void Update();
	SDL_Window* GetHandle();
	void Swap();
	bool KeyDown(const uint8_t AsciiCode);

	int MouseX();
	int MouseY();
	void MouseSetPos(const int32_t X, const int32_t Y);
	bool ButtonDown(const int Button);

	int Width();
	int Height();
};
