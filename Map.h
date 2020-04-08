#pragma once
#include "RAM.h"
#include "Context.h"
#include "Physics.h"

#include <boost/filesystem.hpp>

void LoadMap(const boost::filesystem::path& Path, RAM& mem, std::shared_ptr<Context> Ctx, std::shared_ptr<Physics> Phy, std::vector<Thing*>& GfxComp);
