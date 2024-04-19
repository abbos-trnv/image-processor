#include <vector>
#pragma once
struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    Image();
    Image(int width, int height);
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    int GetWidth() const;
    int GetHeight() const;

    void Read(const char* path);
    void Export(const char* path) const;

private:
    int width_;
    int height_;
    std::vector<Color> m_colors_;
};