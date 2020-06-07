#pragma once

#include "meta-scene/spectrums/spectrum.hpp"

#include "rainbow-cpu/shared/spectrums/spectrum.hpp"

using namespace rainbow::cpus::shared::spectrums;

namespace rainbow::renderer::converter {

	spectrum read_spectrum(const std::shared_ptr<metascene::spectrums::spectrum>& spectrum);
	
}
