#pragma once
#include <stdio.h>
#include "triangle.hpp"

bool load_obj_from_file(const char *file_name, std::vector<Triangle> &triangles);