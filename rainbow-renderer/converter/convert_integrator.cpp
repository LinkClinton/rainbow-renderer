#include "convert_integrator.hpp"

#include "meta-scene/integrators/bidirectional_path_integrator.hpp"
#include "meta-scene/integrators/photon_mapping_integrator.hpp"
#include "meta-scene/integrators/volume_path_integrator.hpp"
#include "meta-scene/integrators/direct_integrator.hpp"
#include "meta-scene/integrators/path_integrator.hpp"

#include "rainbow-core/logs/log.hpp"

#include "rainbow-cpu/integrators/bidirectional_path_integrator.hpp"
#include "rainbow-cpu/integrators/photon_mapping_integrator.hpp"
#include "rainbow-cpu/integrators/volume_path_integrator.hpp"
#include "rainbow-cpu/integrators/direct_integrator.hpp"
#include "rainbow-cpu/integrators/path_integrator.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<integrator> create_path_integrator(
		const std::shared_ptr<metascene::integrators::path_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), integrator->depth, integrator->threshold);
	}

	std::shared_ptr<integrator> create_volume_integrator(
		const std::shared_ptr<metascene::integrators::volume_path_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<volume_path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), integrator->depth, integrator->threshold);
	}

	std::shared_ptr<integrator> create_photon_mapping_integrator(
		const std::shared_ptr<metascene::integrators::photon_mapping_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<photon_mapping_integrator>(
			create_sampler2d(sampler),
			create_sampler1d(sampler),
			integrator->iterations, integrator->depth,
			integrator->photons, integrator->radius);
	}

	std::shared_ptr<integrator> create_bidirectional_path_integrator(
		const std::shared_ptr<metascene::integrators::bidirectional_path_integrator>& integrator,
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		return std::make_shared<bidirectional_path_integrator>(
			create_sampler2d(sampler),
			create_sampler1d(sampler),
			integrator->depth);
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
		if (integrator->type == metascene::integrators::type::bidirectional_path)
			return create_bidirectional_path_integrator(std::static_pointer_cast<metascene::integrators::bidirectional_path_integrator>(integrator), sampler);
		
		if (integrator->type == metascene::integrators::type::photon_mapping)
			return create_photon_mapping_integrator(std::static_pointer_cast<metascene::integrators::photon_mapping_integrator>(integrator), sampler);
		
		if (integrator->type == metascene::integrators::type::volume_path)
			return create_volume_integrator(std::static_pointer_cast<metascene::integrators::volume_path_integrator>(integrator), sampler);
		
		if (integrator->type == metascene::integrators::type::direct)
			return create_direct_integrator(std::static_pointer_cast<metascene::integrators::direct_integrator>(integrator), sampler);

		if (integrator->type == metascene::integrators::type::path)
			return create_path_integrator(std::static_pointer_cast<metascene::integrators::path_integrator>(integrator), sampler);
		
		logs::error("unknown integrator");

		return std::make_shared<path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), 5);
	}
	
}