#include "convert_emitter.hpp"

#include "meta-scene/emitters/environment_emitter.hpp"
#include "meta-scene/emitters/surface_emitter.hpp"

#include "rainbow/emitters/environment_light.hpp"
#include "rainbow/emitters/surface_light.hpp"
#include "rainbow/shared/logs/log.hpp"

#include "../importers/image_importer.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<emitter> create_surface_emitter(const std::shared_ptr<metascene::emitters::surface_emitter>& emitter)
	{
		return std::make_shared<surface_light>(read_spectrum(emitter->radiance));
	}

	std::shared_ptr<emitter> create_environment_emitter(const std::shared_ptr<metascene::emitters::environment_emitter>& emitter)
	{
		if (emitter->environment_map.empty())
			return std::make_shared<environment_light>(read_spectrum(emitter->intensity), 1000.0f);

		return std::make_shared<environment_light>(importers::import_environment_map(emitter->environment_map),
			read_spectrum(emitter->intensity), 1000.0f);
	}
	
	std::shared_ptr<emitter> create_emitter(const std::shared_ptr<metascene::emitters::emitter>& emitter)
	{
		if (emitter == nullptr) return nullptr;
		
		if (emitter->type == metascene::emitters::type::surface)
			return create_surface_emitter(std::static_pointer_cast<metascene::emitters::surface_emitter>(emitter));

		if (emitter->type == metascene::emitters::type::environment)
			return create_environment_emitter(std::static_pointer_cast<metascene::emitters::environment_emitter>(emitter));
		
		logs::error("unknown emitter.");

		return nullptr;
	}
}
