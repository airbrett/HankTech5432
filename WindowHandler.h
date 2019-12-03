#pragma once
#include <SDL.h>

#include <array>

class WindowHandler
{
private:
	SDL_Window* mWnd;
	std::array<uint8_t, 255> mKeys;
	int32_t mMouseX;
	int32_t mMouseY;
	std::array<uint8_t, 3> mButtons;

public:
	WindowHandler();

	void Update();
	SDL_Window* GetHandle();
	void Swap();
	bool KeyDown(const uint8_t AsciiCode);

	int32_t MouseX();
	int32_t MouseY();
	void MouseSetPos(const int32_t X, const int32_t Y);
	bool ButtonDown(const int Button);
};
