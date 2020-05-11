#pragma once

#include "meta-scene/integrators/integrator.hpp"

#include "rainbow/integrators/integrator.hpp"

#include "sampler.hpp"

namespace rainbow {

	using namespace integrators;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<integrator> create_integrator(
				const std::shared_ptr<metascene::integrators::integrator>& integrator,
				const std::shared_ptr<metascene::samplers::sampler>& sampler);
			
		}
	}
}
