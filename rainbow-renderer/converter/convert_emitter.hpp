#pragma once

#include "meta-scene/objects/light.hpp"

#include "rainbow-cpu/emitters/emitter.hpp"

using namespace rainbow::cpus::emitters;

namespace rainbow::renderer::converter {

	std::shared_ptr<emitter> create_emitter(const std::optional<meta_scene::objects::light>& light, real radius);
	
}