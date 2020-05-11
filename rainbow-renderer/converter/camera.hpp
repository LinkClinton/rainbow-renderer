#pragma once

#include "meta-scene/filters/filter.hpp"
#include "meta-scene/cameras/camera.hpp"
#include "meta-scene/cameras/film.hpp"

#include "rainbow/cameras/camera.hpp"
#include "rainbow/cameras/film.hpp"

namespace rainbow {

	using namespace cameras;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<film> create_film(
				const std::shared_ptr<metascene::cameras::film>& film);

			std::shared_ptr<camera> create_camera(
				const std::shared_ptr<metascene::cameras::camera>& camera,
				const std::shared_ptr<metascene::cameras::film>& film);
		}
	}
}
