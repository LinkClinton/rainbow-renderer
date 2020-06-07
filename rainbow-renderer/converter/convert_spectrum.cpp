#include "convert_spectrum.hpp"

#include "meta-scene/spectrums/sampled_spectrum.hpp"
#include "meta-scene/spectrums/color_spectrum.hpp"

#include "rainbow-core/logs/log.hpp"

namespace rainbow::renderer::converter {

	spectrum read_sampled_spectrum(const std::shared_ptr<metascene::spectrums::sampled_spectrum>& spectrum)
	{
		return cpus::shared::spectrums::spectrum(spectrum->lambda, spectrum->value);
	}

	spectrum read_color_spectrum(const std::shared_ptr<metascene::spectrums::color_spectrum>& spectrum)
	{
		return cpus::shared::spectrums::spectrum(spectrum->red, spectrum->green, spectrum->blue);
	}

	spectrum converter::read_spectrum(const std::shared_ptr<metascene::spectrums::spectrum>& spectrum)
	{
		if (spectrum->type == metascene::spectrums::type::color)
			return read_color_spectrum(std::static_pointer_cast<metascene::spectrums::color_spectrum>(spectrum));

		if (spectrum->type == metascene::spectrums::type::sampled)
			return read_sampled_spectrum(std::static_pointer_cast<metascene::spectrums::sampled_spectrum>(spectrum));

		logs::error("unknown spectrum type.");

		return cpus::shared::spectrums::spectrum();
	}
	
}
