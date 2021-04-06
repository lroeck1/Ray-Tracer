#include "parser.h"
#include "material.h"
#include "texture.h"
#include "solid.h"
#include "checkerboard.h"
#include "gradient.h"
#include "glass.h"
#include <sstream>

bool is_type(const std::string& line, const std::string& type);
bool is_whitespace(const std::string& line);
void remove_comment(std::string& line);

Parser::Parser(const std::string& filename)
    : pixels{Pixels{0,0}}, found_rays{false} {

    std::ifstream input(filename);
    if(!input){
        std::string msg{"Could not open " + filename};
        throw std::runtime_error(msg);
    }
    parse(input);
    verify();
}

void Parser::parse(std::ifstream& input){
    std::string line;
    while(std::getline(input, line)){
        remove_comment(line); // remove text after #
        if(is_whitespace(line)){
            continue;
        }
        else if(is_type(line, "pixels")){
            parse_pixels(line);
        }
        else if(is_type(line, "camera")){
            parse_camera(line);
        }
        else if(is_type(line, "sphere")){
            parse_sphere(line);
        }
        else if(is_type(line, "material")){
            parse_material(line);
        }
        else if(is_type(line, "output")){
            parse_output(line);
        }
        else if(is_type(line, "rays")){
            parse_rays(line);
        }
        else if(is_type(line, "triangle")){
            parse_triangle(line);
        }
        else if(is_type(line, "mesh")){
            parse_mesh(line);
        }
        else{
            std::string msg {"Unrecognized type in line: " + line};
            throw std::runtime_error(msg);
        }
    }
}

void Parser::verify(){
    if(aspect == -1){
        std::string msg{"Missing from file: camera"};
        throw std::runtime_error(msg);
    }
    if(pixels.height == 0 && pixels.height == 0){
        std::string msg{"Missing from file: pixels"};
        throw std::runtime_error(msg);
    }
    if(world.objects.empty()){
        std::string msg{"Missing from file: any objects"};
        throw std::runtime_error(msg);
    }
    if(output_filename.empty()){
        std::string msg{"Missing from file: output"};
        throw std::runtime_error(msg);
    }
    if(materials.empty()){
        std::string msg{"Missing from file: materials"};
        throw std::runtime_error(msg);
    }
    if(!found_rays){
        std::string msg{"Missing from file: rays"};
        throw std::runtime_error(msg);
    }
}

void remove_comment(std::string& line){
    auto i = line.find('#');
    if(i != std::string::npos){
        line = line.substr(0,i);
    }
}

bool is_whitespace(const std::string& line){
    return std::all_of(std::begin(line), std::end(line), ::isspace);
}

bool is_type(const std::string& line, const std::string& type){
    return line.find(type) == 0;
}

void Parser::parse_pixels(const std::string &line) {
    unsigned w, h;

    std::stringstream ss;
    ss << line;
    std::string pixelsstring;
    ss >> pixelsstring >> w >> h;

    pixels.width = w;
    pixels.height = h;
    pixels.values.resize(w*h);
    aspect = static_cast<double>(w)/static_cast<double>(h);
}

void Parser::parse_camera(const std::string& line){
    Point3D camera_position, camera_target;
    Vector3D camera_up;
    double camera_fov;

    std::stringstream ss;
    ss << line;
    std::string camerastring;
    ss >> camerastring >> camera_position >> camera_target >> camera_up >> camera_fov;
    c = Cam{camera_position, camera_target, camera_up, camera_fov};
}

void Parser::parse_sphere(const std::string &line) {
    Point3D center;
    double radius;
    std::shared_ptr<Material> m;
    std::stringstream ss;
    ss << line;

    std::string spherestring, material_name;
    ss >> spherestring >> center >> radius >> material_name;
    auto material = materials.find(material_name);
    if(material != materials.end()){
        world.add_sphere(center,radius, material->second);
    }
    else{
        throw std::runtime_error("Cannot find material: " + material_name);
    }
}

void Parser::parse_triangle(const std::string &line){
    Point3D vertex0, vertex1, vertex2;
    std::shared_ptr<Material> m;
    std::stringstream ss;

    ss << line;

    std::string triangle_string, material_name;
    ss >> triangle_string >> vertex0 >> vertex1 >> vertex2 >> material_name;
    auto material = materials.find(material_name);
    if(material != materials.end()){
        world.add_triangle(vertex0, vertex1, vertex2, material->second);
    }
    else{
        throw std::runtime_error("Cannot find material: " + material_name);
    }
}

void Parser::parse_mesh(const std::string &line) {
    std::vector<Vector3D> v;
    Vector3D displacement_vector, vect;
    double x, y, z;
    std::shared_ptr<Material> m;
    std::stringstream ss;

    ss << line;

    std::string mesh_string, filename, material_name;
    ss >> mesh_string >> displacement_vector >> filename >> material_name;

    std::ifstream input(filename);
    if (!input) {
        std::string msg{"Could not open " + filename};
        throw std::runtime_error(msg);
    }

    std::string l;
    std::stringstream str;
    std::getline(input, l);
    remove_comment(l); // remove text after #
    if (is_whitespace(l)) {
        std::getline(input, l);
    }
    while (std::getline(input, l)) {
        if (is_type(l, "triangles")) {
            break;
        }
        str << l;
        str >> vect;
        v.push_back(vect);
    }
    do {
        std::getline(input, l);
        std::stringstream s;
        s << l;
        s >> x >> y >> z;
        auto material = materials.find(material_name);
        if (material != materials.end()) {
            world.add_triangle(v[x] + displacement_vector, v[y] + displacement_vector,
                               v[z] + displacement_vector, material->second);
        }
        else {
            throw std::runtime_error("Cannot find material: " + material_name);
        }
    } while (!input.eof());
}

void Parser::parse_output(const std::string& line){
    std::stringstream ss;
    std::string s;
    ss << line;
    ss >> s >> output_filename;
}

void Parser::parse_material(const std::string& line){
    std::stringstream ss;
    std::string name, kind, m_name, texture_name;
    Color color;
    bool emitting;
    ss << line;
    ss >> m_name >> name >> kind >> texture_name >> color >> std::boolalpha >> emitting;

    if(texture_name == "solid"){
        textures[texture_name] = std::make_shared<Solid>(texture_name, color);
    }
    else if(texture_name == "checkerboard"){
        textures[texture_name] = std::make_shared<Checkerboard>(texture_name, color);
    }
    else if(texture_name == "gradient"){
        textures[texture_name] = std::make_shared<Gradient>(texture_name, color);
    }
    else{
        throw std::runtime_error("Unknown texture: " + texture_name);
    }

    auto texture = textures[texture_name];
    if(kind == "specular"){
        materials[name] = std::make_shared<Specular>(texture, emitting);
    }
    else if (kind == "diffuse"){
        materials[name] = std::make_shared<Diffuse>(texture, emitting);
    }
    else if (kind == "metal"){
        double fuzz;
        if(ss >> fuzz){
            materials[name] = std::make_shared<Metal>(texture, emitting, fuzz);
        }
        else{
            throw std::runtime_error("Fuzzless");
        }
    }
    else if (kind == "impossible"){
        materials[name] = std::make_shared<Impossible>(texture, emitting);
    }
    else if (kind == "glass"){
        materials[name] = std::make_shared<Glass>(texture, emitting);
    }
    else{
        throw std::runtime_error("Unknown material: " + kind);
    }
}

void Parser::parse_rays(const std::string& line){
    std::stringstream ss;
    std::string name;
    ss << line;
    if (ss >> name >> depth >> samples){
        found_rays = true;
    }
    else{
        throw std::runtime_error("Malformed parameters for rays");
    }
}

Camera Parser::get_camera() {
    auto [position, target, up, fov] = c;
    return Camera{position, target, up, fov, aspect};
}

World Parser::get_world() {
    return world;
}

Pixels Parser::get_pixels() {
    return pixels;
}

std::string Parser::get_filename() {
    return output_filename;
}