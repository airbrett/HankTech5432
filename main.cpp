#include "Thing.h"
#include "Context.h"
#include "Physics.h"
#include "RAM.h"
#include "Clock.h"
#include "Player.h"
#include "WindowHandler.h"
#include "Map.h"
#include "DeferredSubmitter.h"

#include <boost/filesystem.hpp>

#include <glm/gtc/matrix_transform.hpp>

int main(char* argv[], int argc)
{
	std::shared_ptr<WindowHandler> Window = std::make_shared<WindowHandler>(1024, 768);
	std::shared_ptr<Context> Ctx = std::make_shared<Context>(Window);
	std::shared_ptr<Physics> Physicser = std::make_shared<Physics>();
	RAM World;
	Clock Time;

	LoadMap("Data\\map1.ht", Ctx, Physicser, World);

	//DeferredSubmitter<Context> DefSub(Ctx.get());
	
	std::shared_ptr<Player> Plr = World.Rez<Player>();

	Plr->Init(Window, Physicser);
	Plr->PhysicalHandle = Physicser->CreateCircle(0.2f, 1.0f, Plr->GetID());
	Physicser->SetPosition(Plr->PhysicalHandle, { 0,0,-20 });

	const double UPDATE_STEP = 1.0 / 60.0;
	double Timer = Time.GetTime();

	Time.Reset();

	while (!Window->KeyDown(27))
	{
		std::vector<std::shared_ptr<Thing>>& Objects = World.GetObjects();

		Time.Step();

		Window->Update();

		//Fixed rate updates
		if (Time.GetTime() > Timer + UPDATE_STEP)
		{
			do
			{
				Timer += UPDATE_STEP;

				Physicser->Update(UPDATE_STEP);
			}
			while (Time.GetTime() > Timer + UPDATE_STEP);

			glm::vec3 Pos;

			for (std::shared_ptr<Thing> T : Objects)
			{
				if (T->PhysicalHandle != Thing::INVALID_HANDLE)
				{
					if (Physicser->GetPos(T->PhysicalHandle, Pos))
						T->SetPos(Pos);
				}
			}
		}

		//Update logic for things
		for (std::shared_ptr<Thing> T : Objects)
			T->Update(Time.GetDT());

		//Cleanup
		std::vector<std::shared_ptr<Thing>>::iterator Iter = std::begin(Objects);

		while (Iter != std::end(Objects))
		{
			if ((*Iter)->PendingDeRez())
			{
				//TODO cleanup physics/graphics handles
				Iter->reset();
				Iter = Objects.erase(Iter);
			}
			else
			{
				Iter++;
			}
		}

		//Update graphics
		const glm::vec3 CameraLook = Plr->TransformPoint({ 0.0f, 0.0f, 1.0f });
		const glm::vec3 CameraUp(0.0, 1.0, 0.0);

		const glm::mat4 Projection = glm::perspective(glm::radians(30.0f), static_cast<float>(Window->Width()) / Window->Height(), 0.1f, 1000.0f);
		const glm::mat4 View = glm::lookAt(Plr->GetPos(), CameraLook, CameraUp);

		Ctx->Clear();
		Ctx->SetProj(Projection);
		
		for (std::shared_ptr<Thing> T : Objects)
		{
			if (T->Gfx.mVtx != Thing::INVALID_HANDLE)
			{
				Ctx->SetProgram(T->Shader);
				Ctx->SetModelView(View * T->GetMatrix());
				Ctx->SetVertexBuffer(T->Gfx.mVtx);
				Ctx->SetIndexBuffer(T->Gfx.mIdx);
				Ctx->SetTex(T->Gfx.mTex);
				Ctx->Submit(T->Gfx.mIdxCount);
			}
		}

		//DefSub.Flush();

		Window->Swap();
	}

	return 0;
}