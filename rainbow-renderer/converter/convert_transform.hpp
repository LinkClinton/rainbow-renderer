#pragma once

#include "meta-scene/types.hpp"

#include "rainbow-cpu/shared/transform.hpp"

using namespace rainbow::cpus::shared;

namespace rainbow::renderer::converter {

	transform read_transform(const meta_scene::matrix4x4& transform);
	
}
