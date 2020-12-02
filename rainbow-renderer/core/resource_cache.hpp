#pragma once

#include "meta-scene/objects/shape.hpp"

#include "rainbow-cpu/shared/spectrums/spectrum.hpp"
#include "rainbow-cpu/textures/image_texture.hpp"
#include "rainbow-cpu/shapes/mesh.hpp"

#include <unordered_map>

using namespace rainbow::cpus::shared::spectrums;
using namespace rainbow::cpus::textures;
using namespace rainbow::cpus::shapes;

namespace rainbow::renderer {

	struct resource_cache final {
		static inline std::unordered_map<std::string, std::shared_ptr<image_texture2d<spectrum>>> spectrum_textures;
		static inline std::unordered_map<std::string, std::shared_ptr<image_texture2d<real>>> real_textures;
		static inline std::unordered_map<std::string, std::shared_ptr<mesh>> meshes;

		static std::shared_ptr<image_texture2d<spectrum>> read_spectrum_texture(const std::string& filename, bool gamma);

		static std::shared_ptr<image_texture2d<real>> read_real_texture(const std::string& filename, bool gamma);

		static std::shared_ptr<mesh> read_ply_mesh(const meta_scene::objects::shape& mesh);

		static std::shared_ptr<mesh> read_obj_mesh(const std::string& filename);
	};

}