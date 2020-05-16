#pragma once

#include "meta-scene/importers/pbrt/pbrt_importer.hpp"

#include "../core/renderer_scene.hpp"

#ifdef __PBRT_IMPORTER__

namespace rainbow {

	namespace renderer {

		namespace importers {

			renderer_scene import_pbrt_scene(const std::string& filename);
			
		}
	}
}

#endif