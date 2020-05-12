#include "importers/mitsuba_importer.hpp"

using namespace rainbow;

int main() {
	const auto scene = rainbow::renderer::importers::import_mitsuba_scene("./../scenes/veach_mi/mi.xml");

	scene.integrator->set_debug_trace_pixel(vector2i(617, 224));
	
	scene.render_to("image");

	system("pause");
}