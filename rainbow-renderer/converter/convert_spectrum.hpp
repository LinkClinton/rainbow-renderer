#pragma once

#include "meta-scene/types.hpp"

#include "rainbow-cpu/shared/spectrums/spectrum.hpp"

using namespace rainbow::cpus::shared::spectrums;

namespace rainbow::renderer::converter {

	spectrum read_spectrum(const meta_scene::spectrum& spectrum);
	
}
