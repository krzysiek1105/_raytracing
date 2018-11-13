#pragma once
#include <vector>

class Texture
{
  public:
    std::vector<unsigned char> bitmap;
    unsigned int width;
    unsigned int height;
};