#pragma once

#include "meta-scene/filters/filter.hpp"

#include "rainbow/filters/filters.hpp"

#include <memory>

namespace rainbow {

	using namespace filters;
	
	namespace renderer {

		namespace converter {
			
			std::shared_ptr<filter> create_filter(const std::shared_ptr<metascene::filters::filter>& filter);
			
		}
	}
}
