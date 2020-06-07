#pragma once

#include "meta-scene/integrators/integrator.hpp"

#include "rainbow-cpu/integrators/integrator.hpp"

#include "convert_sampler.hpp"

using namespace rainbow::cpus::integrators;

namespace rainbow::renderer::converter {

	std::shared_ptr<integrator> create_integrator(
		const std::shared_ptr<metascene::integrators::integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler);
	
}
