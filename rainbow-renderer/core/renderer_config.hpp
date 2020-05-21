#pragma once

#include "rainbow/shared/utilities.hpp"

namespace rainbow {

	namespace renderer {
		
		/*
		 * in uv coordinate system
		 * right hand is :
		 * (0, 1) --- (1, 1)
		 * |               |
		 * |               |
		 * (0, 0) --- (1, 0)
		 * left hand is :
		 * (0, 0) --- (1, 0)
		 * |               |
		 * |               |
		 * (0, 1) --- (1, 1)
		 */
		enum class coordinate_system : uint32 {
			right_hand = 0,
			left_hand = 1
		};
		
		struct renderer_config final {
			renderer_config() = delete;

			static inline coordinate_system camera_system = coordinate_system::right_hand;
			static inline coordinate_system uv_system = coordinate_system::left_hand;
		};
		
	}
}
