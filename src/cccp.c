/*
 CCCP - The C Create Coding Project

 Copyright (C) 2025 George Watson

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
*/

// cccp.c will contain all files needed for dynamic libraries
// Anything not in here should only be linked to the main executable
#define PAUL_IMPLEMENTATION
#include "cccp.h"
#include "./hashtable.c"
#include "./surface.c"
#include "./shader.c"
#include "./audio.c"