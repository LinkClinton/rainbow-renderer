#pragma once

#include "rainbow-cpu/shapes/mesh.hpp"

#include <string>
#include <memory>
#include <vector>

#define __OBJ_IMPORTER__

using namespace rainbow::cpus::shapes;

namespace rainbow::renderer::importers {

#ifdef __OBJ_IMPORTER__
	std::vector<std::shared_ptr<mesh>> load_obj_mesh(const std::string& file_name);
#endif

}