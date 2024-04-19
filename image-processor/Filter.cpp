#include "Filter.h"
Image CropFilter::Apply(const Image& image) const {
    int new_width = std::min(width_, image.GetWidth());
    int new_height = std::min(height_, image.GetHeight());

    Image cropped_image(new_width, new_height);
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            cropped_image.SetColor(image.GetColor(x, y), x, y);
        }
    }

    return cropped_image;
}
CropFilter::CropFilter(int width, int height) : width_(width), height_(height) {
}
