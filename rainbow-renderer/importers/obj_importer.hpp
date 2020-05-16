#pragma once

#include "rainbow/shapes/mesh.hpp"

#include <string>
#include <memory>
#include <vector>

#define __OBJ_IMPORTER__

namespace rainbow {

	using namespace shapes;

	namespace renderer {

		namespace importers {

#ifdef __OBJ_IMPORTER__
			std::vector<std::shared_ptr<mesh>> load_obj_mesh(const std::string& file_name);
#endif

		}
	}
}
