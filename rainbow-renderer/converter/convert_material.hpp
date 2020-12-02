#pragma once

#include "meta-scene/objects/material.hpp"

#include "rainbow-cpu/materials/material.hpp"

using namespace rainbow::cpus::materials;

#include <optional>

namespace rainbow::renderer::converter {

	std::shared_ptr<material> create_material(const std::optional<meta_scene::objects::material>& material);

}
