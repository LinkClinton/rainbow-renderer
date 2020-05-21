#include "importers/mitsuba_importer.hpp"
#include "importers/pbrt_importer.hpp"

using namespace rainbow;

int main() {
	// these scenes are passed
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/cbox/cbox.xml");
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/veach_mi/mi.xml");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dragon/f8-10.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/metal.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/arcsphere.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/microcity.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/lte-orb/lte-orb-silver.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/yeahright/yeahright.pbrt");

	// these scenes should test again
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/transparent-machines/frame542.pbrt");

	// these scenes are used for test properties
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/xyz-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/uv-test.pbrt");
	
	scene.render_to("image");

	system("pause");
}