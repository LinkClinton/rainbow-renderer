#include "convert_integrator.hpp"

#include "meta-scene/integrators/direct_integrator.hpp"
#include "meta-scene/integrators/path_integrator.hpp"

#include "rainbow/integrators/direct_integrator.hpp"
#include "rainbow/integrators/path_integrator.hpp"
#include "rainbow/shared/logs/log.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<integrator> create_path_integrator(
		const std::shared_ptr<metascene::integrators::path_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), integrator->depth);
	}

	std::shared_ptr<integrator> create_direct_integrator(
		const std::shared_ptr<metascene::integrators::direct_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<direct_integrator>(create_sampler2d(sampler), create_sampler1d(sampler),
			integrator->emitter_samples, integrator->bsdf_samples);
	}

	std::shared_ptr<integrator> converter::create_integrator(
		const std::shared_ptr<metascene::integrators::integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		if (integrator->type == metascene::integrators::type::direct)
			return create_direct_integrator(std::static_pointer_cast<metascene::integrators::direct_integrator>(integrator), sampler);

		if (integrator->type == metascene::integrators::type::path)
			return create_path_integrator(std::static_pointer_cast<metascene::integrators::path_integrator>(integrator), sampler);
		
		logs::error("unknown integrator");

		return std::make_shared<path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), 5);
	}
	
}