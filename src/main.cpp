#include "includes/raytracer.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;

    clock_t start = clock();

    Scene scene(argv[2]);

    FILE *f = fopen("o.raw", "wb");
    unsigned char **bitmap = new unsigned char *[scene.camera.height];
    for (int i = 0; i < scene.camera.height; i++)
        bitmap[i] = new unsigned char[scene.camera.width];

    int thread_count = atoi(argv[1]);
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; i++)
        threads.push_back(std::thread(render, std::ref(scene), std::ref(bitmap), i, thread_count));

    for (int i = 0; i < thread_count; i++)
        threads[i].join();

    for (int i = 0; i < scene.camera.height; i++)
        fwrite(bitmap[i], sizeof(unsigned char), scene.camera.width, f);
    fclose(f);

    system("cls");
    printf("100.00%%\nt = %.3fs\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    printf("Total triangles: %llu\n", scene.triangles.size());
    for(int i = 0; i < 8; i++)
        printf("%llu ", scene.octtree.nodes[i].triangles.size());
    return 0;
}