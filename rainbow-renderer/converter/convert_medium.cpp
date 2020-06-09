#include "convert_medium.hpp"

#include "meta-scene/media/homogeneous_medium.hpp"

#include "rainbow-cpu/media/homogeneous_medium.hpp"

#include "rainbow-core/logs/log.hpp"

#include "convert_spectrum.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<medium> create_homogeneous_medium(const std::shared_ptr<metascene::media::homogeneous_medium>& medium)
	{
		return std::make_shared<homogeneous_medium>(read_spectrum(medium->sigma_a), read_spectrum(medium->sigma_s), medium->g);
	}
	
	std::shared_ptr<medium> create_medium(const std::shared_ptr<metascene::media::medium>& medium)
	{
		if (medium == nullptr) return nullptr;

		if (medium->type == metascene::media::type::homogeneous)
			return create_homogeneous_medium(std::static_pointer_cast<metascene::media::homogeneous_medium>(medium));
		
		logs::error("unknown medium.");

		return nullptr;
	}

	std::shared_ptr<media> create_media(const std::shared_ptr<metascene::media::media>& media)
	{
		if (media == nullptr) return nullptr;
		
		return std::make_shared<cpus::media::media>(create_medium(media->outside), create_medium(media->inside));
	}
}
