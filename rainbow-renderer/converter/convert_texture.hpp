#pragma once

#include "meta-scene/textures/texture.hpp"

#include "rainbow/shared/spectrums/spectrum.hpp"
#include "rainbow/textures/texture.hpp"

namespace rainbow {

	using namespace spectrums;
	using namespace textures;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<texture2d<spectrum>> create_spectrum_texture(const std::shared_ptr<metascene::textures::texture>& texture);

			std::shared_ptr<texture2d<real>> create_real_texture(const std::shared_ptr<metascene::textures::texture>& texture); 
		}
		
	}
}
