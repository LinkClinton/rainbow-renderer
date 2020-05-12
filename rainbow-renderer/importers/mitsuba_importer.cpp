#include "mitsuba_importer.hpp"

#include "rainbow/shared/logs/log.hpp"

#ifdef __MITSUBA_IMPORTER__

namespace rainbow::renderer::importers {

	renderer_scene import_mitsuba_scene(const std::string& filename)
	{
		const auto meta_scene = metascene::importers::mitsuba::import_mitsuba_scene(filename);

		for (const auto& entity : meta_scene->entities) {
			if (entity->emitter != nullptr)
				logs::info(entity->emitter->to_string());

			if (entity->material != nullptr)
				logs::info(entity->material->to_string());

			if (entity->shape != nullptr)
				logs::info(entity->shape->to_string());
		}
		
		return create_from_meta_scene(meta_scene);
	}
	
}

#endif
