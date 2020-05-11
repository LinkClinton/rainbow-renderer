#pragma once

#include "meta-scene/spectrums/spectrum.hpp"

#include "rainbow/shared/spectrums/spectrum.hpp"

namespace rainbow {

	using namespace spectrums;
	
	namespace renderer {

		namespace converter {

			spectrum read_spectrum(const std::shared_ptr<metascene::spectrums::spectrum>& spectrum);
			
		}
	}
}
