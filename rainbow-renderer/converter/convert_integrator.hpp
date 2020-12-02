#pragma once

#include "meta-scene/objects/integrator.hpp"

#include "rainbow-cpu/integrators/integrator.hpp"

#include "convert_sampler.hpp"

using namespace rainbow::cpus::integrators;

namespace rainbow::renderer::converter {

	std::shared_ptr<integrator> create_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler);
	
}
