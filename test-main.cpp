#include "pixels.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"
#include "world.h"
#include "parser.h"
#include "hit.h"
#include "random.h"
#include <iomanip>
//#include <mpi.h>

Color trace(const World& w, const Ray& r, int);
void print_progress(long long ray_num, long long total_rays);
void trace_scene(const World& world, const Camera& camera, int depth, int samples, Pixels& pixels);
void pack(Pixels &p, std::vector<double>& send_data);
Pixels unpack(std::vector<double>& recv_data, std::vector<double>& send_data, const Pixels p, int num_processes);

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cout << "Usage: program filename" << std::endl;
            return 1;
        }

        Parser parser(argv[1]);

        Pixels p = parser.get_pixels();
        Camera c = parser.get_camera();
        World w = parser.get_world();
        int depth = parser.depth;
        int samples = parser.samples;

        trace_scene(w, c, depth, samples, p);

        p.save_png(parser.get_filename());
        std::cout << "\nWrote: " << parser.get_filename() << std::endl;
    }
    catch(std::exception& err){
        std::cout << err.what() << '\n';
    }
}

Color trace(const World& w, const Ray& r, int depth) {
    if (depth == 0) {
        return Black;
    }
    auto[time, nearest] = w.find_nearest_object(r);

    if (!nearest) {
        return Black; // sky or ambient light (background)
    }

    Hit h = nearest->construct_hit(time, r);
    auto material = h.material;

    std::pair<double, double> u_v = nearest->uv(h);
    if(material->emitting){
        return material->texture->uv(u_v.first, u_v.second);
    }
    Ray scattered = material->scatter(r, h);
    return trace(w, scattered, depth-1) * material->texture->uv(u_v.first, u_v.second);
}

void print_progress(long long ray_num, long long total_rays){
    auto width = std::to_string(total_rays).length() + 4;
    std::cout.imbue(std::locale(""));
    int percentage = std::round(static_cast<double>(ray_num) / total_rays * 100.0);
    std::cout << "\rProgress: " << std::setw(3) << percentage << "% ";
    std::cout << std::setw(width) << ray_num << '/' << total_rays << " rays";
    std::cout << std::flush;
}

void trace_scene(const World& w, const Camera& c, int depth, int samples, Pixels& p) {
    const long long rays_total = p.height * p.width * static_cast<long long>(samples);
    long long ray_num = 0;
    print_progress(ray_num, rays_total);

    for (int i = 0; i < p.height; i++) {
        for (int j = 0; j < p.width; j++) {
            Color color{0, 0, 0};
            for (int s = 0; s < samples; s++) {
                double y = static_cast <double> (i + random_double()) / static_cast<double> (p.height - 1);
                double x = static_cast <double> (j + random_double()) / static_cast <double> (p.width - 1);
                Ray r = c.compute_ray(x, y);
                color += trace(w, r, depth);
                ++ray_num;
                if (ray_num % (rays_total / 100) == 0) {
                    print_progress(ray_num, rays_total);
                }
            }
            p(i, j) = color / samples;
        }
    }
}