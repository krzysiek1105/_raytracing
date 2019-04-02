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
        int pixelCount = scene.camera.width * scene.camera.height;
        bitmap.resize(pixelCount * 3);

        std::vector<std::thread> threads;
        unsigned int threadCount = std::thread::hardware_concurrency();
        std::atomic<int> pixelsDone = 0;
        for (unsigned int i = 0; i < threadCount; i++)
            threads.push_back(std::thread(render, std::ref(scene), std::ref(bitmap), i, threadCount, &pixelsDone));

        while (pixelsDone != pixelCount)
        {
            printf("Raytracing.. \t%.2lf%%\n", 100 * (double)pixelsDone.load() / pixelCount);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        for (unsigned int i = 0; i < threadCount; i++)
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