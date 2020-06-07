#pragma once

#include "meta-scene/textures/texture.hpp"

#include "rainbow-cpu/shared/spectrums/spectrum.hpp"
#include "rainbow-cpu/textures/texture.hpp"

using namespace rainbow::cpus::shared::spectrums;
using namespace rainbow::cpus::textures;

namespace rainbow::renderer::converter {

	std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::texture>& texture);

	std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::texture>& texture);
	
}
