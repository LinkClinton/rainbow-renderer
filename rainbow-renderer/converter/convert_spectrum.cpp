#include "convert_spectrum.hpp"

#include "rainbow-core/logs/log.hpp"

namespace rainbow::renderer::converter {

	spectrum converter::read_spectrum(const meta_scene::spectrum& spectrum)
	{
		return cpus::shared::spectrums::spectrum(spectrum);
		
		logs::error("unknown spectrum type.");

		return cpus::shared::spectrums::spectrum();
	}
	
}
