#include "Thing.h"
#include "Instance.h"
#include "Draw.h"
#include "Physics.h"
#include "RAM.h"
#include "Player.h"
#include "WindowHandler.h"

#include <array>
#include <vector>

int main(char* argv[], int argc)
{
	std::shared_ptr<Instance> Inst = std::make_shared<Instance>();

	std::shared_ptr<WindowHandler> Window = std::make_shared<WindowHandler>();
	std::shared_ptr<Draw> Drawer = std::make_shared<Draw>(Window);
	Physics Physicser(&Inst->Things);
	RAM Rammer(&Inst->Things);

	Inst->Drawerizor = Drawer;
	Inst->Window = Window;

	Thing* A = Rammer.Rez<Thing>();

	A->SetPos(-5, 0, 0);

	Thing* B = Rammer.Rez<Thing>();

	B->SetPos(5, 0, 0);

	Player* Plr = Rammer.Rez<Player>();

	Plr->Init(Window);
	Plr->SetPos(0.0, 0.0, -20);

	Inst->Camera = Plr;

	Uint32 Time = SDL_GetTicks();

	while (!Window->KeyDown(27))
	{
		const float Now = (SDL_GetTicks() - Time) / 1000.0f;

		for (Thing* T : Inst->Things)
			T->Update(Now);

		Window->Update();
		Physicser.Update();
		Drawer->Update(Plr, &Inst->Things);
		Inst->Window->Swap();
		Rammer.Update();
		

		SDL_Delay(10);
	}

	return 0;
}