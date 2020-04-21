#pragma once
#include "Context.h"
#include "Physics.h"
#include "RAM.h"

#include <boost/filesystem.hpp>

void LoadMap(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Physics> Phy, RAM& World);
