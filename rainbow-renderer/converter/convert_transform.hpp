#pragma once

#include "meta-scene/math/matrix4x4.hpp"

#include "rainbow-cpu/shared/transform.hpp"

using namespace rainbow::cpus::shared;

namespace rainbow::renderer::converter {

	transform read_transform(const metascene::math::matrix4x4& transform);
	
}
