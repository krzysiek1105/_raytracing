#include "includes/raytracer.hpp"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Error (%d): use following parameters <scene_name> <output_file_name>\n", 1);
        return 1;
    }

    clock_t start = clock();

    std::unique_ptr<Scene> scene;
    try
    {
        scene = std::make_unique<Scene>(argv[1]);
    }
    catch(int e)
    {
        printf("Error (%d): could not read %s\n", e, argv[1]);
        return e;   
    }

    FILE *f = fopen(argv[2], "wb");
    if(f == nullptr)
    {
        printf("Error: could not create file %s\n", argv[2]);
        return 1;
    }

    std::vector<unsigned char> bitmap;
    bitmap.reserve(scene->camera.width * scene->camera.height);

    std::vector<std::thread> threads;
    unsigned int thread_count = std::thread::hardware_concurrency();
    for (unsigned int i = 0; i < thread_count; i++)
        threads.push_back(std::thread(render, std::ref(*scene), std::ref(bitmap), i, thread_count));
    for (unsigned int i = 0; i < thread_count; i++)
        threads[i].join();

    fwrite(&bitmap[0], sizeof(unsigned char), scene->camera.width * scene->camera.height, f);
    fclose(f);

    system("cls");
    printf("Done in %.3lf seconds\n", (clock() - (double)start) / CLOCKS_PER_SEC);
    return 0;
}