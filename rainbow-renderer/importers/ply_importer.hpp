#pragma once

#include "meta-scene/shapes/triangles.hpp"
#include "meta-scene/shapes/mesh.hpp"

#include "rainbow/shapes/mesh.hpp"

#include <string>

#define __PLY_IMPORTER__
#ifndef __PLY_IMPORTER__
#else

namespace rainbow {

	using namespace shapes;
	
	namespace renderer {

		namespace importers {

			std::shared_ptr<metascene::shapes::triangles> load_ply_mesh(const std::string& filename);
		}
	}
}

#endif