#include "importers/mitsuba_importer.hpp"
#include "importers/pbrt_importer.hpp"

using namespace rainbow;

int main() {
	// these scenes are passed
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/cbox/cbox.xml");
	//const auto scene = renderer::importers::import_mitsuba_scene("./../scenes/veach_mi/mi.xml");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dragon/f8-10.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/lte-orb/lte-orb-silver.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/metal.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/arcsphere.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/microcity.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/yeahright/yeahright.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/transparent-machines/frame542.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/transparent-machines/frame675.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/transparent-machines/frame812.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/pbrt-book/book.pbrt"); // not support bump mapping
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/ganesha/ganesha.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/killeroos/killeroo-gold.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/chopper-titan/chopper-titan.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/tt/tt.pbrt"); // not support bump mapping
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/buddha-fractal/buddha-fractal.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/bathroom/bathroom.pbrt"); // replace fourier material to mixture material
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/landscape/view-0.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/crown/crown.pbrt"); // not support bump mapping
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/ecosys/ecosys.pbrt"); //not support windy texture and bump mapping
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/bmw-m6/bmw-m6.pbrt"); // replace fourier material to substrate material
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/vw-van/vw-van.pbrt"); // replace fourier material to matte material

	// bssrdf 
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/sssdragon/dragon_10.pbrt"); 
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/cbox-sss/cbox.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/structuresynth/ballpile.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/head/head.pbrt");

	// volume scattering
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dragon/f11-14.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/coffee-splash/splash.pbrt"); // the distance of environment is fixed
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dambreak/dambreak0.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/cloud/cloud.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/cloud/smoke.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/smoke-plume/plume-084.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/smoke-plume/plume-184.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/smoke-plume/plume-284.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/volumetric-caustic/scene.pbrt");	
	
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/bedroom/scene.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/kitchen/scene.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/staircase2/scene.pbrt"); 
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/living-room-3/scene.pbrt"); 
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/water-caustic/scene.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/cornell-box/scene.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/bunny-fur/f3-15.pbrt");

	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/veach-bidir/scene.pbrt");
	
	// these scenes should test again
	const auto scene = renderer::importers::import_pbrt_scene("./../scenes/measure-one/frame380.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/measure-one/frame300.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/breakfast/breakfast-lamps.pbrt"); //no triangle list mesh
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/sanmiguel/sanmiguel_cam25.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/barcelona-pavilion/pavilion-day.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/sportscar/sportscar.pbrt"); //ply mesh
	
	// these scenes are used for test properties
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/xyz-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/uv-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/directional-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/mixture-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/glass-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/curve-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/sppm-test.pbrt");
	//const auto scene = renderer::importers::import_pbrt_scene("./../scenes/basic-test/volume-test.pbrt");

	
	//scene.integrator->set_debug_trace_pixel(vector2i(729, 466));
	//scene.integrator->set_debug_trace_pixel(vector2i(1191, 422));
	
	scene.render_to("image");

	system("pause");
}