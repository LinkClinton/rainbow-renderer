#pragma once

#include "meta-scene/importers/mitsuba/mitsuba_importer.hpp"

#include "../core/renderer_scene.hpp"

namespace rainbow {

	namespace renderer {

		namespace importers {

#ifdef __MITSUBA_IMPORTER__
			renderer_scene import_mitsuba_scene(const std::string& filename);
#endif

		}		
	}
}
