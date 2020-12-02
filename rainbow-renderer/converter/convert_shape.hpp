#pragma once

#include "meta-scene/objects/shape.hpp"

#include "rainbow-cpu/shapes/shape.hpp"

using namespace rainbow::cpus::shapes;

namespace rainbow::renderer::converter {

	std::shared_ptr<shape> create_shape(const std::optional<meta_scene::objects::shape>& shape);
	
}
