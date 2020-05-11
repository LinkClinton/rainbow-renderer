#pragma once

#include "meta-scene/math/matrix4x4.hpp"

#include "rainbow/shared/transform.hpp"

namespace rainbow {

	namespace renderer {

		namespace converter {

			transform read_transform(const metascene::math::matrix4x4& transform);
			
		}
	}
}
