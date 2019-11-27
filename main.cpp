#include "Thing.h"
#include "Instance.h"
#include "Draw.h"
#include "Physics.h"
#include "RAM.h"
#include "User.h"
#include "Player.h"

#include <array>
#include <vector>

int main(char* argv[], int argc)
{
	Instance Inst;

	Draw Drawer(&Inst);
	Physics Physicser(&Inst.Things);
	RAM Rammer(&Inst.Things);
	User Blerg(&Inst.Keys);

	Thing* A = Rammer.Rez<Thing>();

	A->SetPos(-5, 0, 0);

	Thing* B = Rammer.Rez<Thing>();

	B->SetPos(5, 0, 0);

	Player* Plr = Rammer.Rez<Player>();

	Plr->Init(&Inst);
	Plr->SetPos(0.0, 0.0, -20);

	Inst.Camera = Plr;

	Uint32 Time = SDL_GetTicks();

	while (true)
	{
		const float Now = (SDL_GetTicks() - Time) / 1000.0f;

		for (Thing* T : Inst.Things)
			T->Update(Now);

		Physicser.Update();
		Drawer.Update();
		Rammer.Update();
		Blerg.Update();

		SDL_Delay(10);
	}

	return 0;
}