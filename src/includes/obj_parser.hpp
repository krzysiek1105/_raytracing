#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include "triangle.hpp"
#include "material.hpp"

bool loadOBJFromFile(const char *fileName, std::vector<Triangle> &triangles, std::unordered_map<std::string, Material> &materials);
bool loadMTLFromFile(const char *fileName, std::unordered_map<std::string, Material> &materials);
int findSeparatorInPath(const char *const path);