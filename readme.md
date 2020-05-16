# Rainbow-Renderer

Rainbow-renderer is a simple physical based renderer.

Rainbow-renderer is based `rainbow` and `meta-scene`.

- [Rainbow](https://github.com/LinkClinton/rainbow) : Core of renderer. 
- [Meta-Scene](https://github.com/LinkClinton/meta-scene) : Scene importer.

## Build

- Clone or download the repository and submodules.
```
git clone https://github.com/LinkClinton/rainbow-renderer.git

git submodule update --init --recursive
```
- Using `vcpkg` to install third-parties.
- Open `.sln` with Visual Studio 2019 and build it.

## Scene

Now only support part of `mitsuba` scene format and part of `pbrt-v3` scene. See more in [meta-scene](https://github.com/LinkClinton/meta-scene). It is a library to load different scene format.

## ThirdParties

- [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) : Tiny but powerful single file wavefront obj loader.
- [tinyply](https://github.com/ddiakopoulos/tinyply) : 🌍 C++11 ply 3d mesh format importer & exporter.
- [stb_image](https://github.com/nothings/stb) : stb single-file public domain libraries for C/C++.

`tinyply` is not a package of vcpkg. So we have a copy of it in [libraries](./libraries/tinyply).

## Gallery

[A Mitsuba conversion of the classic Cornell Box scene.](http://mitsuba-renderer.org/download.html)

![cbox](./gallery/cbox.png)

[Multiple importance sampling test — based on a scene by Eric Veach](http://mitsuba-renderer.org/download.html)

![mi](./gallery/mi.png)

[Dragon with Environment](https://pbrt.org/resources.html)

![dragon-32spp](./gallery/f8-10.png)