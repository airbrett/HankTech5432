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
	std::shared_ptr<Physics> Physicser = std::make_shared<Physics>(Inst, &Inst->Things);
	RAM Rammer(&Inst->Things);

	Inst->Window = Window;

	Thing* A = Rammer.Rez<Thing>();

	A->PhysComp = Physicser->CreateComponent(A);
	A->PhysComp->SetShape(PhysicsComponent::SQUARE, 1.0f);
	A->PhysComp->SetPosition({ -5,0,0 });

	A->GfxComp = Ctx->CreateComponent(A);
	A->GfxComp->SetModel();

	Thing* B = Rammer.Rez<Thing>();

	B->PhysComp = Physicser->CreateComponent(B);
	B->PhysComp->SetShape(PhysicsComponent::SQUARE, 1.0f);
	B->PhysComp->SetPosition({ 5,0,0 });
	
	B->GfxComp = Ctx->CreateComponent(B);
	B->GfxComp->SetModel();
	

	Player* Plr = Rammer.Rez<Player>();

	Plr->Init(Window, Physicser);
	Plr->PhysComp = Physicser->CreateComponent(Plr);
	Plr->PhysComp->SetShape(PhysicsComponent::CIRCLE, 0.4f);
	Plr->PhysComp->SetMass(1.0f);
	Plr->PhysComp->SetPosition({ 0,0,-20 });

	std::vector<uint8_t> TexBytes;
	unsigned int W, H;
	lodepng::decode(TexBytes, W, H, "Data\\Wall.png");
	Ctx->LoadTexture(TexBytes.data(), TexBytes.size(), W, H);

	Inst->Camera = Plr;

	Uint32 Time = SDL_GetTicks();

	Inst->Time.Reset();

	while (!Window->KeyDown(27))
	{
		const float Now = SDL_GetTicks();
		const float dt = (Now - Time) / 1000.0f;
		Inst->Time.Step();

		Time = Now;

		for (Thing* T : Inst->Things)
			T->Update(dt);

		Window->Update();
		Physicser->Update();
		Ctx->Update(Plr);
		Inst->Window->Swap();
		Rammer.Update();
	}

	return 0;
}