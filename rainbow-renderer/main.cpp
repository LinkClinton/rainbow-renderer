#include "importers/mitsuba_importer.hpp"
#include "importers/pbrt_importer.hpp"

using namespace rainbow;

int main() {
	const auto scene = renderer::importers::import_pbrt_scene("./../scenes/dragon/f8-10.pbrt");

	scene.render_to("image");

	system("pause");
}

