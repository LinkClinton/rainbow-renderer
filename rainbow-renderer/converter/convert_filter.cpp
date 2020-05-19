#include "convert_filter.hpp"

#include "meta-scene/filters/gaussian_filter.hpp"
#include "meta-scene/filters/box_filter.hpp"

#include "rainbow/filters/gaussian_filter.hpp"
#include "rainbow/filters/box_filter.hpp"
#include "rainbow/shared/logs/log.hpp"

namespace rainbow::renderer::converter {

	std::shared_ptr<filter> create_gaussian_filter(const std::shared_ptr<metascene::filters::gaussian_filter>& filter)
	{
		return std::make_shared<gaussian_filter>(vector2(filter->radius_x, filter->radius_y), filter->alpha);
	}

	std::shared_ptr<filter> create_box_filter(const std::shared_ptr<metascene::filters::box_filter>& filter)
	{
		return std::make_shared<box_filter>(vector2(filter->radius_x, filter->radius_y));
	}

	std::shared_ptr<filter> create_filter(const std::shared_ptr<metascene::filters::filter>& filter)
	{
		if (filter->type == metascene::filters::type::gaussian)
			return create_gaussian_filter(std::static_pointer_cast<metascene::filters::gaussian_filter>(filter));

		if (filter->type == metascene::filters::type::box)
			return create_box_filter(std::static_pointer_cast<metascene::filters::box_filter>(filter));

		logs::error("unknown filter.");

		return std::make_shared<box_filter>();
	}
}
