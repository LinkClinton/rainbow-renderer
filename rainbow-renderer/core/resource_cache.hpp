#pragma once

#include "rainbow/shared/spectrums/spectrum.hpp"
#include "rainbow/textures/image_texture.hpp"
#include "rainbow/shapes/mesh.hpp"

#include <unordered_map>

namespace rainbow {

	using namespace spectrums;
	using namespace textures;
	using namespace shapes;
	
	namespace renderer {

		struct resource_cache final {
			static inline std::unordered_map<std::string, std::shared_ptr<image_texture2d<spectrum>>> spectrum_textures;
			static inline std::unordered_map<std::string, std::shared_ptr<image_texture2d<real>>> real_textures;
			static inline std::unordered_map<std::string, std::shared_ptr<mesh>> meshes;
			
			static std::shared_ptr<image_texture2d<spectrum>> read_spectrum_texture(const std::string& filename, bool gamma);

			static std::shared_ptr<image_texture2d<real>> read_real_texture(const std::string& filename, bool gamma);

			static std::shared_ptr<mesh> read_ply_mesh(const std::string& filename);

			static std::shared_ptr<mesh> read_obj_mesh(const std::string& filename);
		};
		
	}
}
