#include "Helpers.h"
#include <filesystem>

#define AZ_PI 3.14159265359 

namespace Az
{


    void SetWorkingDir()
    {
        std::filesystem::path currentDir = std::filesystem::current_path();
        std::filesystem::path parentDir = currentDir.parent_path();
        std::string folderName = currentDir.filename().string();

        std::cout << "Current Folder: " << folderName << std::endl;

        if (folderName == "Debug")
        {
            currentDir = parentDir.parent_path();
            std::filesystem::current_path(currentDir);

            std::cout << "Changed working directory to: " << std::filesystem::current_path() << std::endl;
        }

        else if (folderName == "Release")
        {
            currentDir = parentDir.parent_path();
            std::filesystem::current_path(currentDir);

            std::cout << "Changed working directory to: " << std::filesystem::current_path() << std::endl;
        }

    }

    float DistanceBetweenPoints(const glm::vec3& p1, const glm::vec3& p2)
    {
        return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
    }

    glm::vec3 rotatePoint(glm::vec3 point, glm::vec3 ref, float rad)
    {
        glm::mat4 rotationMatrix = glm::rotate(rad, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z-axis

        glm::vec4 translatedPoint = glm::vec4(point - ref, 1.0f); // Move point relative to ref
        glm::vec4 rotatedPoint = rotationMatrix * translatedPoint; // Apply rotation
        return glm::vec3(rotatedPoint) + ref; // Move point back
    }

    float PixelsToMeters(float pixels)
    {
        return pixels / PIXEL_PER_METER;
    }

    float MetersToPixels(float meters)
    {
        return meters * PIXEL_PER_METER;
    }


    float toDegrees(float radian)
    {
        return radian * (180 / AZ_PI);
    }

    float toRadians(float degree)
    {
        return degree * (AZ_PI / 180);
    }

    float normalize(float min, float max, float value)
    {
        return (value - min) / (max - min);
    }

    float deNormalize(float min, float max, float value)
    {
        return (value * (max - min)) - min;
    }

    float getRandomFloat(float min, float max)
    {
        if (min > max) std::swap(min, max);

        float num = static_cast<float>(rand()) / RAND_MAX * (max - min) + min;

        return num;
    }

    int getRandomInt(int min, int max)
    {
        if (min > max) std::swap(min, max);

        int num = rand() % (max - min + 1) + min;

        return num;
    }

    int getRandomInt(int max)
    {
        int num = rand() % max;
        return num;
    }

}

