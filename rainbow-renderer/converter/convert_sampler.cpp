#include "convert_sampler.hpp"

#include "rainbow-cpu/samplers/random_sampler.hpp"

#include "rainbow-core/logs/log.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<sampler1d> create_random_sampler1d(const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<random_sampler1d>(sampler.sample_per_pixel);
	}

	std::shared_ptr<sampler2d> create_random_sampler2d(const meta_scene::objects::sampler& sampler)
	{
		return std::make_shared<random_sampler2d>(sampler.sample_per_pixel);
	}

	std::shared_ptr<sampler1d> converter::create_sampler1d(const meta_scene::objects::sampler& sampler)
	{
		if (sampler.type == "random") return create_random_sampler1d(sampler);

		logs::error("unknown sampler.");

		return std::make_shared<random_sampler1d>(16);
	}

	std::shared_ptr<sampler2d> converter::create_sampler2d(const meta_scene::objects::sampler& sampler)
	{
		if (sampler.type == "random") return create_random_sampler2d(sampler);

		logs::error("unknown sampler.");

		return std::make_shared<random_sampler2d>(16);
	}

	
}