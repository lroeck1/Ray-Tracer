#pragma once
#include <fstream>
#include <iostream>
#include "camera.h"
#include "world.h"
#include "pixels.h"
#include "sphere.h"
#include <memory>
#include "specular.h"
#include "diffuse.h"
#include "metal.h"
#include "impossible.h"
#include <tuple>
#include <map>

class Material;
class Texture;

using Cam = std::tuple <Point3D, Point3D, Vector3D, double>;
using Materials = std::map<std::string, std::shared_ptr<Material>>;
using Textures = std::map<std::string, std::shared_ptr<Texture>>;

class Parser{
public:
    Parser(const std::string & filename);
    void parse(std::ifstream& input);
    Camera get_camera();
    World get_world();
    Pixels get_pixels();
    std::string get_filename();
    void verify();

    int depth, samples;
private:
    void parse_camera(const std::string& line);
    void parse_pixels(const std::string& line);
    void parse_sphere(const std::string& line);
    void parse_output(const std::string& line);
    void parse_material(const std::string& line);
    void parse_rays(const std::string& line);
    void parse_triangle(const std::string& line);
    void parse_mesh(const std::string& line);

    Materials materials;
    Textures textures;
    World world;
    Pixels pixels;
    std::string output_filename;
    Cam c;
    double aspect;
    bool found_rays;
};