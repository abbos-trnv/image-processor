#include "Image.h"
#include "Filter.h"
#include <iostream>
#include <vector>
#include <string>

void PrintUsage() {
    std::cout << "Usage: image_processor <input_file> <output_file> [-crop <width> <height>]" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        PrintUsage();
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];
    // Список фильтров
    std::vector<std::string> filters;
    std::vector<std::vector<float>> parameters;

    // Парсинг аргументов командной строки
    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-crop") {
            if (i + 2 >= argc) {
                std::cerr << "Error: Missing crop parameters." << std::endl;
                return 1;
            }
            filters.push_back(arg);
            std::vector<float> params;
            params.push_back(std::stof(argv[++i]));
            params.push_back(std::stof(argv[++i]));
            parameters.push_back(params);
        } else {
            std::cerr << "Error: Unknown filter or incorrect parameters: " << arg << std::endl;
            return 1;
        }
    }

    try {
        // Загрузка изображения
        Image image;
        image.Read(input_file.c_str());

        // Применение фильтров
        for (size_t i = 0; i < filters.size(); ++i) {
            if (filters[i] == "-crop") {
                if (parameters[i].size() != 2) {
                    std::cerr << "Error: Incorrect number of parameters for crop filter." << std::endl;
                    return 1;
                }
                int width = static_cast<int>(parameters[i][0]);
                int height = static_cast<int>(parameters[i][1]);
                CropFilter crop_filter(width, height);
                image = crop_filter.Apply(image);
            }
        }

        // Сохранение отфильтрованного изображения
        image.Export(output_file.c_str());
    } catch (...) {
        std::cerr << "Error: Image processing failed." << std::endl;
        return 1;
    }

    return 0;
}