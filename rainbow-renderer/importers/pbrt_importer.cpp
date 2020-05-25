#include "pbrt_importer.hpp"

#include "../core/renderer_config.hpp"

#include "rainbow/shared/logs/log.hpp"

#ifdef __PBRT_IMPORTER__

rainbow::renderer::renderer_scene rainbow::renderer::importers::import_pbrt_scene(const std::string& filename)
{
	const auto meta_scene = metascene::importers::pbrt::import_pbrt_scene(filename);

	for (const auto& entity : meta_scene->entities)
		logs::info(entity->to_string());
	
	renderer_config::camera_system = coordinate_system::left_hand;
	renderer_config::uv_system = coordinate_system::right_hand;
	
	return create_from_meta_scene(meta_scene);
}

#endif