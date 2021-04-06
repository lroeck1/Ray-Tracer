#include "pixels.h"
#include "lodepng.h"
#include <fstream>
#include <cmath>

Pixels::Pixels()
    :width{0}, height{0}, values{0}{}

Pixels::Pixels(unsigned width, unsigned height)
  :width{width}, height{height}, values(width*height) {}

const Color& Pixels::operator()(unsigned i, unsigned j) const {
    return values[i*width +j];
}

Color& Pixels::operator()(unsigned i, unsigned j) {
    return values[i*width +j];
}

void Pixels::save_ppm(const std::string& filename) {
    std::ofstream output(filename);
    std::fstream input;
    if (!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    std::vector<unsigned int> data;
    for (int i = 0; i < values.size(); i++) {
        data.push_back(to_color<unsigned>(values[i].x));
        data.push_back(to_color<unsigned>(values[i].y));
        data.push_back(to_color<unsigned>(values[i].z));
    }
    for (int i = 0; i < values.size(); i++) {
        input << data[i] << " ";
    }
}

void Pixels::save_png(const std::string& filename) {
    std::ofstream output(filename);
    if(!output) {
        throw std::runtime_error("Cannot open output file: " + filename);
    }
    std::vector<unsigned char> data;
    for (auto c : values) {
        data.push_back(to_color<unsigned char>(c.x));
        data.push_back(to_color<unsigned char>(c.y));
        data.push_back(to_color<unsigned char>(c.z));
        data.push_back(255);
    }
    unsigned error = lodepng::encode(filename, data, width, height);
    if (error) {
        throw std::runtime_error(lodepng_error_text(error));
    }
}

double gamma_correction(double value) {
  // double gamma = 2.2;
  double gamma = 1.0;
  return std::pow(value, 1/gamma);
}
