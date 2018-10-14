#include "includes/raytracer.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;

    clock_t start = clock();

    std::vector<Triangle> triangles;
    if (!load_obj_from_file(argv[2], triangles))
    {
        printf("Error: %s not found\n", argv[2]);
        return 2;
    }

    std::vector<Light> lights;
    lights.push_back(Light(Vector(0.0, -1.0, 0.0), 0.5));
    lights.push_back(Light(Vector(0.0, -1.0, 1.0), 0.5));
    lights.push_back(Light(Vector(-1.0, 0.0, 0.0), 0.25));

    Camera camera(WIDTH, HEIGHT, FOV, Vector(3.0, 3.75, 3.0), Vector(-10.0, 70.0, 30.0));
    // Camera camera(WIDTH, HEIGHT, FOV, Vector(0.0, 1.0, 1.5), Vector(-45.0, 0.0, 0.0));

    Octtree octtree(triangles);

    FILE *f = fopen("o.raw", "wb");
    unsigned char **bitmap = new unsigned char *[HEIGHT];
    for (int i = 0; i < HEIGHT; i++)
        bitmap[i] = new unsigned char[WIDTH];

    int THREAD_COUNT = atoi(argv[1]);
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; i++)
        threads.push_back(std::thread(render, std::ref(octtree), std::ref(lights), std::ref(camera), std::ref(bitmap), i, THREAD_COUNT));

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();

    for (int i = 0; i < HEIGHT; i++)
        fwrite(bitmap[i], sizeof(unsigned char), WIDTH, f);
    fclose(f);

    system("cls");
    printf("100.00%%\nt = %.3fs\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    printf("Total triangles: %llu\n", triangles.size());
    for(int i = 0; i < 8; i++)
        printf("%llu ", octtree.nodes[i].triangles.size());
    return 0;
}