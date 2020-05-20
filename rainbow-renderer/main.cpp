#include "importers/mitsuba_importer.hpp"
#include "importers/pbrt_importer.hpp"

using namespace rainbow;

int main() {
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/cbox/cbox.xml");
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/veach_mi/mi.xml");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dragon/f8-10.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/xyz-test/xyz-test.pbrt");
	const auto scene = renderer::importers::import_pbrt_scene("./../scenes/lte-orb/lte-orb-silver.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/yeahright/yeahright.pbrt");

	scene.render_to("image");

	system("pause");
}
