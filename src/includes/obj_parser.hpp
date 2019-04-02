#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include "triangle.hpp"
#include "material.hpp"

bool loadOBJFromFile(const char *file_name, std::vector<Triangle> &triangles, std::unordered_map<std::string, Material> &materials);
bool loadMTLFromFile(const char *file_name, std::unordered_map<std::string, Material> &materials);