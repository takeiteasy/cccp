# CCCP 

The *C* *C*reative *C*oding *P*roject

## TODO

- [X] ~~Reimplement dylib reloading~~
- [X] ~~Image loading from file (and exporting)~~ (stb_image + qoi)
    - [ ] GIF/Video recording/exporting?
    - [ ] Export surface to image file (stb_image_write + qoi)
- [X] ~~Shaders (multithreaded software renderer)~~
- [X] ~~Generate noise, gradient surfaces, etc.~~
- [ ] Text rendering (font8x8 + stb_truetype)
- [X] ~~Target FPS control~~
- [X] ~~Audio management~~ (raudio)
- [ ] Dynamic rebuilding of scenes (dmon)
- [ ] Packaging for different platforms?
- [ ] 3D API? (using software rasterizer + software shaders)
- [ ] Test on Linux and Windows (only tested on macOS)
- [ ] Export web builds (emscripten) (no dynamic loading of scenes)

## Dependencies

- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
- [stb_image_write.h](https://github.com/nothings/stb/blob/master/stb_image_write.h)
- [stb_vorbis.h](https://github.com/nothings/stb/blob/master/stb_vorbis.h)
- [phoboslab/qoi](https://github.com/phoboslab/qoi) [MIT]
- [phoboslab/qoa](https://github.com/phoboslab/qoa) [MIT]
- [dhepper/font8x8](https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h) [Public Domain]
- [skandhurkat/Getopt-for-Visual-Studio](https://github.com/skandhurkat/Getopt-for-Visual-Studio) [GNU GPLv3]
- [dlfcn-win32/dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32) [MIT]
- Inspired by this [blog post](https://nullprogram.com/blog/2014/12/23/) by [skeeto](https://github.com/skeeto/interactive-c-demo) [UNLICENSE]
- [raudio](https://github.com/raysan5/raudio) [zlib/libpng]
- [mackron/miniaudio](https://github.com/mackron/miniaudio) [Public Domain]
- [mackron/dr_libs](https://github.com/mackron/dr_libs) [Public Domain]
- jar_xm.h by Romain "Artefact2" Dalmaso [WTFPL]
- jar_mod.h by Romain "Artefact2" Dalmaso [Public Domain]

## License
```
The C Creative Coding Project (CCCP)

Copyright (C) 2024  George Watson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
