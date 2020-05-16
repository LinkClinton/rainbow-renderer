#pragma once

#include "rainbow/shapes/mesh.hpp"


#include <string>

#define __PLY_IMPORTER__
#ifndef __PLY_IMPORTER__
#else

namespace rainbow {

	using namespace shapes;
	
	namespace renderer {

		namespace importers {

			std::shared_ptr<mesh> load_ply_mesh(const std::string& filename);
			
		}
	}
}

#endif