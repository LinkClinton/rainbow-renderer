#include "convert_filter.hpp"

#include "rainbow-core/logs/log.hpp"
#include "rainbow-cpu/filters/gaussian_filter.hpp"
#include "rainbow-cpu/filters/box_filter.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<filter> create_gaussian_filter(const meta_scene::objects::filter& filter)
	{
		return std::make_shared<gaussian_filter>(vector2(filter.radius_x, filter.radius_y), filter.gaussian.alpha);
	}

	std::shared_ptr<filter> create_box_filter(const meta_scene::objects::filter& filter)
	{
		return std::make_shared<box_filter>(vector2(filter.radius_x, filter.radius_y));
	}

	std::shared_ptr<filter> create_filter(const meta_scene::objects::filter& filter)
	{
		if (filter.type == "gaussian") return create_gaussian_filter(filter);
		if (filter.type == "box") return create_box_filter(filter);

		logs::error("unknown filter.");

		return std::make_shared<box_filter>();
	}
}
