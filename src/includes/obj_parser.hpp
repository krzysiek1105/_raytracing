#pragma once
#include <stdio.h>
#include <string.h>
#include "triangle.hpp"
#include "material.hpp"

bool load_obj_from_file(const char *file_name, std::vector<Triangle> &triangles, std::vector<Material> &materials);
bool load_mtl_from_file(const char *file_name, std::vector<Material> &materials);