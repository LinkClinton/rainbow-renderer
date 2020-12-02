#include "convert_transform.hpp"

transform rainbow::renderer::converter::read_transform(const meta_scene::matrix4x4& transform)
{
	return cpus::shared::transform(transform, inverse(transform));
}
