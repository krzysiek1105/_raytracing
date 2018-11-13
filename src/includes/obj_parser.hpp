#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include "triangle.hpp"
#include "material.hpp"
#include "texture.hpp"

bool load_obj_from_file(const char *file_name, std::vector<Triangle> &triangles, std::unordered_map<std::string, Material> &materials);
bool load_mtl_from_file(const char *file_name, std::unordered_map<std::string, Material> &materials);
bool load_texture_from_file(const char *file_name, Texture &texture);