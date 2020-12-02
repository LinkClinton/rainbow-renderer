#pragma once

#include "meta-scene/objects/texture.hpp"

#include "rainbow-cpu/shared/spectrums/spectrum.hpp"
#include "rainbow-cpu/textures/texture.hpp"

using namespace rainbow::cpus::shared::spectrums;
using namespace rainbow::cpus::textures;

namespace rainbow::renderer::converter {

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const meta_scene::objects::texture& texture);

	std::shared_ptr<texture2d<real>> create_real_texture(const meta_scene::objects::texture& texture);
	
}
