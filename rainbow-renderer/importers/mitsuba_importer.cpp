#include "mitsuba_importer.hpp"

#ifdef __MITSUBA_IMPORTER__

namespace rainbow::renderer::importers {

	renderer_scene importers::load_mitsuba_scene(const std::string& filename)
	{
		const auto meta_scene = metascene::importers::load_mitsuba_scene(filename);

		return create_from_meta_scene(meta_scene);
	}
	
}

#endif
