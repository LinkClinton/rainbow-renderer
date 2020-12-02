#pragma once

#include "meta-scene/objects/filter.hpp"

#include "rainbow-cpu/filters/filters.hpp"

#include <memory>

using namespace rainbow::cpus::filters;

namespace rainbow::renderer::converter {

	std::shared_ptr<filter> create_filter(const meta_scene::objects::filter& filter);

}
