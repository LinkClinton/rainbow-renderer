#pragma once

#include "meta-scene/objects/medium.hpp"

#include "rainbow-cpu/media/medium.hpp"

using namespace rainbow::cpus::media;

namespace rainbow::renderer::converter {

	std::shared_ptr<medium> create_medium(const std::optional<meta_scene::objects::medium>& medium);

	std::shared_ptr<media> create_media(const std::optional<meta_scene::objects::media>& media);
}
