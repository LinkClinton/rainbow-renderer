#pragma once

#include "meta-scene/shapes/shape.hpp"

#include "rainbow/shapes/shape.hpp"

namespace rainbow {

	using namespace shapes;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<shape> create_shape(const std::shared_ptr<metascene::shapes::shape>& shape);
			
		}
	}
}
