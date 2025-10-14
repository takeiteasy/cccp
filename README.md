# cccp 

The **C** **C**reative **C**oding **P**roject (CCCP) is a simple, cross-platform framework for making creative coding projects in C. It provides hot-reloading of scenes, window + input handling, multithreaded software shaders, audio playback, image loading, and text rendering.

![Preview](/preview.gif)

This project is inspired by [skeeto's interactive C demo](https://nullprogram.com/blog/2014/12/23/). For a full list of 3rd party dependencies, see the *[Dependencies](#dependencies)* section below. See *[TODO](#todo)* for planned features. Supported target platforms are macOS (Cocoa), Linux (X11), and Windows (WinAPI) with `clang` or `gcc`. Web builds (Emscripten) are planned.

## How to use

```
 usage: cccp [path to dylib] [options]

 cccp  Copyright (C) 2024  George Watson
 This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 This is free software, and you are welcome to redistribute it
 under certain conditions; type `show c' for details.

 Options:
     -w/--width     Window width [default: 640]
     -h/--height    Window height [default: 480]
     -t/--title     Window title [default: "CCCP"]
     -r/--resizable Enable resizable window
     -a/--top       Enable window always on top
     -u/--usage     Display this message
```

1. Create a new C file for your scene, e.g. `myscene.c`, and put it in the `scenes/` directory. You can use `scenes/example.c` as a template.
2. Build the project using `make all`.
3. Run the program with your scene: `./build/cccp build/myscene.dylib` (on macOS, .so on Linux, .dll on Windows)
4. Edit your scene code and recompile it with `make scenes` while the program is running to see your changes live!
5. ???
6. Profit!

## Building

```
git clone https://github.com/takeiteasy/cccp.git
cd cccp
mkdir build
make all
```

## TODO

- [X] ~~Reimplement dylib reloading~~
- [X] ~~Image loading from file (and exporting)~~ (stb_image + qoi)
    - [ ] GIF/Video recording/exporting?
    - [ ] Export surface to image file (stb_image_write + qoi)
- [X] ~~Shaders (multithreaded software renderer)~~
- [X] ~~Generate noise, gradient surfaces, etc.~~
- [X] ~~Text rendering~~ (font8x8 + stb_truetype)
- [X] ~~Target FPS control~~
- [X] ~~Audio management~~ (raudio)
- [ ] Dynamic rebuilding of scenes (dmon)
- [ ] Packaging for different platforms?
- [ ] 3D API? (using software rasterizer + software shaders)
- [ ] Test on Linux and Windows (only tested on macOS)
- [ ] Export web builds (emscripten) (no dynamic loading of scenes)

## Dependencies

- [nothings/stb](https://github.com/nothings/stb/) [Public Domain]
    - stb_vorbis.c, stb_truetype.h, stb_image.h, stb_image_write.h
- [phoboslab/qoi](https://github.com/phoboslab/qoi) [MIT]
- [phoboslab/qoa](https://github.com/phoboslab/qoa) [MIT]
- [dhepper/font8x8](https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h) [Public Domain]
- [skandhurkat/Getopt-for-Visual-Studio](https://github.com/skandhurkat/Getopt-for-Visual-Studio) [GNU GPLv3]
- [dlfcn-win32/dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32) [MIT]
- [raysan5/raudio](https://github.com/raysan5/raudio) [zlib/libpng]
    - [mackron/miniaudio](https://github.com/mackron/miniaudio) [Public Domain]
    - [mackron/dr_libs](https://github.com/mackron/dr_libs) [Public Domain]
        - dr_wav.h, dr_flac.h, dr_mp3.h
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
