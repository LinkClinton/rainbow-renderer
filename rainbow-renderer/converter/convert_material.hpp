#pragma once

#include "meta-scene/materials/material.hpp"

#include "rainbow-cpu/materials/material.hpp"

using namespace rainbow::cpus::materials;

namespace rainbow::renderer::converter {

	std::shared_ptr<material> create_material(const std::shared_ptr<metascene::materials::material>& material);

}
