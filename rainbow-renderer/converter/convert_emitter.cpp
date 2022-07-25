#include "convert_emitter.hpp"

#include "rainbow-core/logs/log.hpp"
#include "rainbow-cpu/emitters/environment_light.hpp"
#include "rainbow-cpu/emitters/directional_light.hpp"
#include "rainbow-cpu/emitters/surface_light.hpp"

#include "../importers/image_importer.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<emitter> create_surface_emitter(const meta_scene::objects::light& light)
	{
		return std::make_shared<surface_light>(read_spectrum(light.intensity));
	}

	std::shared_ptr<emitter> create_environment_emitter(const meta_scene::objects::light& light, real radius)
	{
		if (light.environment.image.empty())
			return std::make_shared<environment_light>(read_spectrum(light.intensity), radius);

		return std::make_shared<environment_light>(
			importers::import_environment_map(renderer_config::directory_path + light.environment.image, light.environment.gamma),
			read_spectrum(light.intensity), radius);
	}

	std::shared_ptr<emitter> create_directional_emitter(const meta_scene::objects::light& light, real radius)
	{
		return std::make_shared<directional_light>(
			read_spectrum(light.intensity),
			light.directional.direction, radius);
	}

	std::shared_ptr<emitter> create_emitter(const std::optional<meta_scene::objects::light>& light, real radius)
	{
		if (!light.has_value()) return nullptr;
		
		if (light->type == "surface") return create_surface_emitter(light.value());
		if (light->type == "directional") return create_directional_emitter(light.value(), radius);
		if (light->type == "environment") return create_environment_emitter(light.value(), radius);
		
		logs::error("unknown emitter.");

		return nullptr;
	}
}
