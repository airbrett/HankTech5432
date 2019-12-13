#include "Thing.h"
#include "Instance.h"
#include "Context.h"
#include "Physics.h"
#include "RAM.h"
#include "Player.h"
#include "WindowHandler.h"

#include "lodepng.h"

#include <array>
#include <vector>

int main(char* argv[], int argc)
{
	std::shared_ptr<Instance> Inst = std::make_shared<Instance>();

	std::shared_ptr<WindowHandler> Window = std::make_shared<WindowHandler>(1024, 768);
	std::shared_ptr<Context> Ctx = std::make_shared<Context>(Window);
	std::shared_ptr<Physics> Physicser = std::make_shared<Physics>(&Inst->Things);
	RAM Rammer(&Inst->Things);

	Inst->Window = Window;

	Thing* A = Rammer.Rez<Thing>();

	//A->SetPos(-5, 0, 0);
	Physicser->AddThingSquare(A, 1.0f, 1.0f, 0.0f);
	Physicser->SetThingPos(A, -5, 0);

	Thing* B = Rammer.Rez<Thing>();

	//B->SetPos(5, 0, 0);
	Physicser->AddThingSquare(B, 1.0f, 1.0f, 0.0f);
	Physicser->SetThingPos(B, 5, 0);

	

	Player* Plr = Rammer.Rez<Player>();

	Plr->Init(Window, Physicser);
	//Plr->SetPos(0.0, 0.0, -20);
	Physicser->AddThingCircle(Plr, 0.4f, 1.0f);
	Physicser->SetThingPos(Plr, 0, -20);

	std::vector<uint8_t> TexBytes;
	unsigned int W, H;
	lodepng::decode(TexBytes, W, H, "Data\\Wall.png");
	Ctx->LoadTexture(TexBytes.data(), TexBytes.size(), W, H);

	Inst->Camera = Plr;

	Uint32 Time = SDL_GetTicks();

	while (!Window->KeyDown(27))
	{
		const float dt = (SDL_GetTicks() - Time) / 1000.0f;

		for (Thing* T : Inst->Things)
			T->Update(dt);

		Window->Update();
		Physicser->Update(dt);
		Ctx->Update(Plr, &Inst->Things);
		Inst->Window->Swap();
		Rammer.Update();
		

		SDL_Delay(10);
	}

	return 0;
}