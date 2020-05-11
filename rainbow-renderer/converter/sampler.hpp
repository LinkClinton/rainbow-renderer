#pragma once

#include "meta-scene/samplers/sampler.hpp"

#include "rainbow/samplers/samplers.hpp"

namespace rainbow {

	using namespace samplers;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<sampler1d> create_sampler1d(const std::shared_ptr<metascene::samplers::sampler>& sampler);

			std::shared_ptr<sampler2d> create_sampler2d(const std::shared_ptr<metascene::samplers::sampler>& sampler);

		}
	}
}
