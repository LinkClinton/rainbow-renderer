#include "pbrt_importer.hpp"

#include "rainbow/shared/logs/log.hpp"

#ifdef __PBRT_IMPORTER__

rainbow::renderer::renderer_scene rainbow::renderer::importers::import_pbrt_scene(const std::string& filename)
{
	const auto meta_scene = metascene::importers::pbrt::import_pbrt_scene(filename);

	return create_from_meta_scene(meta_scene);
}

#endif