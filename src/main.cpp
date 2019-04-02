#include "includes/raytracer.hpp"
#include <thread>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Error: use following parameters <scene_name> <output_file_name>\n");
        return 1;
    }

    try
    {
        clock_t start = clock();
        printf("Building the scene..\n");
        Scene scene(argv[1]);

        FILE *f = fopen(argv[2], "wb");
        if (f == nullptr)
        {
            printf("Error: could not create file %s\n", argv[2]);
            return 1;
        }

        printf("Starting raytracer..\n");
        std::vector<unsigned char> bitmap;
        int pixel_count = scene.camera.width * scene.camera.height;
        bitmap.resize(pixel_count * 3);

        std::vector<std::thread> threads;
        unsigned int thread_count = std::thread::hardware_concurrency();
        std::atomic<int> pixelsDone = 0;
        for (unsigned int i = 0; i < thread_count; i++)
            threads.push_back(std::thread(render, std::ref(scene), std::ref(bitmap), i, thread_count, &pixelsDone));

        while (pixelsDone != pixel_count)
        {
            printf("Raytracing.. \t%.2lf%%\n", 100 * (double)pixelsDone.load() / pixel_count);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        for (unsigned int i = 0; i < thread_count; i++)
            threads[i].join();

        printf("Saving bitmap..\n");
        fwrite(&bitmap[0], sizeof(unsigned char), bitmap.size(), f);
        fclose(f);

        printf("Done in %.3lf seconds\n", (clock() - (double)start) / CLOCKS_PER_SEC);
        return 0;
    }
    catch (const std::invalid_argument &e)
    {
        printf("Error: %s\n", e.what());
        return 2;
    }
}