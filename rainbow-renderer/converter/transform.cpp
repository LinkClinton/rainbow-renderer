#include "transform.hpp"

rainbow::transform rainbow::renderer::converter::read_transform(const metascene::math::matrix4x4& transform)
{
	return rainbow::transform(transform, inverse(transform));
}
