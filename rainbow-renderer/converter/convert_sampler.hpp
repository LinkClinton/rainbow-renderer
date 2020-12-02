#pragma once

#include "meta-scene/objects/sampler.hpp"

#include "rainbow-cpu/samplers/samplers.hpp"

using namespace rainbow::cpus::samplers;

namespace rainbow::renderer::converter {

	std::shared_ptr<sampler1d> create_sampler1d(const meta_scene::objects::sampler& sampler);

	std::shared_ptr<sampler2d> create_sampler2d(const meta_scene::objects::sampler& sampler);
	
}
