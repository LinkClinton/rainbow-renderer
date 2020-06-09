#pragma once

#include "meta-scene/media/medium.hpp"

#include "rainbow-cpu/media/medium.hpp"

using namespace rainbow::cpus::media;

namespace rainbow::renderer::converter {

	std::shared_ptr<medium> create_medium(const std::shared_ptr<metascene::media::medium>& medium);

	std::shared_ptr<media> create_media(const std::shared_ptr<metascene::media::media>& media);
}
