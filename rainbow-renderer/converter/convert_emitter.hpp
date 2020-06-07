#pragma once

#include "meta-scene/emitters/emitter.hpp"

#include "rainbow-cpu/emitters/emitter.hpp"

using namespace rainbow::cpus::emitters;

namespace rainbow::renderer::converter {

	std::shared_ptr<emitter> create_emitter(const std::shared_ptr<metascene::emitters::emitter>& emitter);
	
}