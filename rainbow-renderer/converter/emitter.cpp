#include "emitter.hpp"

#include "meta-scene/emitters/surface_emitter.hpp"

#include "rainbow/emitters/surface_light.hpp"
#include "rainbow/shared/logs/log.hpp"

#include "spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<emitter> create_surface_emitter(const std::shared_ptr<metascene::emitters::surface_emitter>& emitter)
	{
		return std::make_shared<surface_light>(read_spectrum(emitter->radiance));
	}

	std::shared_ptr<emitter> create_emitter(const std::shared_ptr<metascene::emitters::emitter>& emitter)
	{
		if (emitter == nullptr) return nullptr;
		
		if (emitter->type == metascene::emitters::type::surface)
			return create_surface_emitter(std::static_pointer_cast<metascene::emitters::surface_emitter>(emitter));

		logs::error("unknown emitter.");

		return nullptr;
	}
}
