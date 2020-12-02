#pragma once

#include "meta-scene/objects/shape.hpp"

#include "rainbow-cpu/shapes/mesh.hpp"

#include <string>

#define __PLY_IMPORTER__
#ifndef __PLY_IMPORTER__
#else

namespace rainbow::renderer::importers {

	std::shared_ptr<meta_scene::objects::internal::triangles> load_ply_mesh(const std::string& filename);
	
}

#endif