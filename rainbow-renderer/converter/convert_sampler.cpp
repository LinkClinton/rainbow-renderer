#include "convert_sampler.hpp"

#include "meta-scene/samplers/random_sampler.hpp"

#include "rainbow/samplers/random_sampler.hpp"
#include "rainbow/shared/logs/log.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<sampler1d> create_random_sampler1d(
		const std::shared_ptr<metascene::samplers::random_sampler>& sampler)
	{
		return std::make_shared<random_sampler1d>(sampler->sample_per_pixel);
	}

	std::shared_ptr<sampler2d> create_random_sampler2d(
		const std::shared_ptr<metascene::samplers::random_sampler>& sampler)
	{
		return std::make_shared<random_sampler2d>(sampler->sample_per_pixel);
	}

	std::shared_ptr<sampler1d> converter::create_sampler1d(
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		if (sampler->type == metascene::samplers::type::random)
			return create_random_sampler1d(std::static_pointer_cast<metascene::samplers::random_sampler>(sampler));

		logs::error("unknown sampler.");

		return std::make_shared<random_sampler1d>(16);
	}

	std::shared_ptr<sampler2d> converter::create_sampler2d(
		const std::shared_ptr<metascene::samplers::sampler>& sampler)
	{
		if (sampler->type == metascene::samplers::type::random)
			return create_random_sampler2d(std::static_pointer_cast<metascene::samplers::random_sampler>(sampler));

		logs::error("unknown sampler.");

		return std::make_shared<random_sampler2d>(16);
	}

	
}