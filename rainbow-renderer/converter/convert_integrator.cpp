#include "convert_integrator.hpp"

#include "rainbow-core/logs/log.hpp"

#include "rainbow-cpu/integrators/bidirectional_path_integrator.hpp"
#include "rainbow-cpu/integrators/photon_mapping_integrator.hpp"
#include "rainbow-cpu/integrators/volume_path_integrator.hpp"
#include "rainbow-cpu/integrators/direct_integrator.hpp"
#include "rainbow-cpu/integrators/path_integrator.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<integrator> create_path_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<path_integrator>(
			create_sampler2d(sampler), create_sampler1d(sampler), 
			integrator.depth, integrator.path.threshold);
	}

	std::shared_ptr<integrator> create_volume_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<volume_path_integrator>(
			create_sampler2d(sampler), create_sampler1d(sampler),
			integrator.depth, integrator.path.threshold);
	}

	std::shared_ptr<integrator> create_photon_mapping_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<photon_mapping_integrator>(
			create_sampler2d(sampler),
			create_sampler1d(sampler),
			integrator.photon_mapping.iterations, integrator.depth,
			integrator.photon_mapping.photons, integrator.photon_mapping.radius);
	}

	std::shared_ptr<integrator> create_bidirectional_path_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<bidirectional_path_integrator>(
			create_sampler2d(sampler),
			create_sampler1d(sampler),
			integrator.depth);
	}
	
	std::shared_ptr<integrator> create_direct_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<direct_integrator>(create_sampler2d(sampler), create_sampler1d(sampler),
			integrator.direct.light_samples, integrator.direct.bsdf_samples);
	}

	std::shared_ptr<integrator> converter::create_integrator(
		const meta_scene::objects::integrator& integrator,
		const meta_scene::objects::sampler& sampler)
	{
		if (integrator.type == "bidirectional_path") return create_bidirectional_path_integrator(integrator, sampler);
		if (integrator.type == "photon_mapping") return create_photon_mapping_integrator(integrator, sampler);
		if (integrator.type == "volume_path") return create_volume_integrator(integrator, sampler);
		if (integrator.type == "direct") return create_direct_integrator(integrator, sampler);
		if (integrator.type == "path") return create_path_integrator(integrator, sampler);
		
		logs::error("unknown integrator");

		return std::make_shared<path_integrator>(create_sampler2d(sampler), create_sampler1d(sampler), 5);
	}
	
}