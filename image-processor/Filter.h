#include "Image.h"
#pragma once
class CropFilter {
public:
    CropFilter(int i, int i1);
    Image Apply(const Image& image) const;

private:
    int width_;
    int height_;
};