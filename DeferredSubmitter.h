#pragma once
#include <queue>
#include <vector>

typedef std::size_t Command;

namespace Commands
{
	enum
	{
		Clear,
		SetProj,
		SetModelView,
		SetVtx,
		SetIdx,
		SetTex,
		SetProg,
		Submit
	};
}

template <typename GDriver>
class DeferredSubmitter
{
private:
	GDriver* mDriver;
	std::vector<glm::mat4> mMtx;
	std::queue<std::size_t> mCmds;

public:
	DeferredSubmitter(GDriver* Driver) :
		mDriver(Driver)
	{}

	void Clear()
	{
		mCmds.emplace(Commands::Clear);
	}

	void SetProj(const glm::mat4& Proj)
	{
		const std::size_t Index = mMtx.size();
		mMtx.emplace_back(Proj);

		mCmds.emplace(Commands::SetProj);
		mCmds.emplace(Index);
	}

	void SetModelView(const glm::mat4& View)
	{
		const std::size_t Index = mMtx.size();
		mMtx.emplace_back(View);

		mCmds.emplace(Commands::SetModelView);
		mCmds.emplace(Index);
	}

	void SetVertexBuffer(const std::size_t Buff)
	{
		mCmds.emplace(Commands::SetVtx);
		mCmds.emplace(Buff);
	}

	void SetIndexBuffer(const std::size_t Buff)
	{
		mCmds.emplace(Commands::SetIdx);
		mCmds.emplace(Buff);
	}

	void SetTex(const std::size_t Tex)
	{
		mCmds.emplace(Commands::SetTex);
		mCmds.emplace(Tex);
	}

	void SetProgram(const std::size_t Prog)
	{
		mCmds.emplace(Commands::SetProg);
		mCmds.emplace(Prog);
	}

	void Submit(const std::size_t Count)
	{
		mCmds.emplace(Commands::Submit);
		mCmds.emplace(Count);
	}

	void Flush()
	{
		while (!mCmds.empty())
		{
			switch (mCmds.front())
			{
			case Commands::Clear:
				mCmds.pop();
				mDriver->Clear();
				break;
			case Commands::SetProj:
				mCmds.pop();

				mDriver->SetProj(mMtx[mCmds.front()]);
				mCmds.pop();
				break;

			case Commands::SetModelView:
				mCmds.pop();

				mDriver->SetModelView(mMtx[mCmds.front()]);
				mCmds.pop();
				break;

			case Commands::SetVtx:
				mCmds.pop();

				mDriver->SetVertexBuffer(mCmds.front());
				mCmds.pop();
				break;

			case Commands::SetIdx:
				mCmds.pop();

				mDriver->SetIndexBuffer(mCmds.front());
				mCmds.pop();
				break;

			case Commands::SetTex:
				mCmds.pop();

				mDriver->SetTex(mCmds.front());
				mCmds.pop();
				break;

			case Commands::SetProg:
				mCmds.pop();

				mDriver->SetProgram(mCmds.front());
				mCmds.pop();
				break;

			case Commands::Submit:
				mCmds.pop();

				mDriver->Submit(mCmds.front());
				mCmds.pop();

				break;
			};
		}

		mMtx.clear();
	}
};