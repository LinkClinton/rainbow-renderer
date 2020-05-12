#include "mitsuba_importer.hpp"

#ifdef __MITSUBA_IMPORTER__

namespace rainbow::renderer::importers {

	renderer_scene import_mitsuba_scene(const std::string& filename)
	{
		const auto meta_scene = metascene::importers::mitsuba::import_mitsuba_scene(filename);

		return create_from_meta_scene(meta_scene);
	}
	
}

#endif
