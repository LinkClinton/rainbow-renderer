#pragma once

#include "meta-scene/emitters/emitter.hpp"

#include "rainbow/emitters/emitter.hpp"

namespace rainbow {

	using namespace emitters;
	
	namespace renderer {

		namespace converter {

			std::shared_ptr<emitter> create_emitter(const std::shared_ptr<metascene::emitters::emitter>& emitter);
			
		}
	}
}
