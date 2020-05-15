#include "importers/mitsuba_importer.hpp"

#include "meta-scene/importers/pbrt/pbrt_importer.hpp"

using namespace rainbow;

int main() {
	metascene::importers::pbrt::import_pbrt_scene("./../scenes/dragon/f8-10.pbrt");
	
	/*const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/cbox/cbox.xml");

	scene.render_to("image");

	system("pause");*/
}