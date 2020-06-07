#pragma once

#include "meta-scene/shapes/shape.hpp"

#include "rainbow-cpu/shapes/shape.hpp"

using namespace rainbow::cpus::shapes;

namespace rainbow::renderer::converter {

	std::shared_ptr<shape> create_shape(const std::shared_ptr<metascene::shapes::shape>& shape);
	
}
