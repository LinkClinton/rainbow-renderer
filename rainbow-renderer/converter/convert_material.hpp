#pragma once

#include "meta-scene/materials/material.hpp"

#include "rainbow/materials/material.hpp"

namespace rainbow {

	using namespace materials;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<material> create_material(const std::shared_ptr<metascene::materials::material>& material);
			
		}
	}
}
