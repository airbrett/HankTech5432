#include "Map.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

void LoadMap(const boost::filesystem::path& Path, RAM& mem, std::shared_ptr<Context> Ctx, std::shared_ptr<Physics> Phy, std::vector<GraphicsComponent*>& GfxComp)
{
	const boost::filesystem::path MapRoot = Path.parent_path();
	boost::property_tree::ptree MapTree;
	boost::property_tree::read_info(Path.string(), MapTree);

	for (boost::property_tree::ptree::value_type& Node : MapTree)
	{
		if (Node.first == "thing")
		{
			Thing* T = mem.Rez<Thing>();

			const std::string Shape = Node.second.get("physics.shape", "");

			if (!Shape.empty())
			{
				if (Shape == "square")
				{
					T->PhysComp = Phy->CreateComponent(T);
					T->PhysComp->SetShape(PhysicsComponent::SQUARE, Node.second.get<float>("physics.shape.size"));
				}
			}

			const std::string Gfx = Node.second.get("graphics", "");

			if (!Gfx.empty())
			{
				GraphicsComponent* Comp = Ctx->CreateComponent(T);

				GfxComp.push_back(Comp);
				T->GfxComp = Comp;
				T->GfxComp->SetModel(MapRoot / Gfx);
			}

			if (!Node.second.get_child("pos").empty())
			{
				if (T->PhysComp != nullptr)//eh...
				{
					T->PhysComp->SetPosition({
						Node.second.get<float>("pos.x"),
						Node.second.get<float>("pos.y"),
						Node.second.get<float>("pos.z")
					});
				}
			}
		}
	}
}
