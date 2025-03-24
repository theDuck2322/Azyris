#pragma once
#include <utils/Types.h>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp> // For glm::rotate
#include <glm/gtc/constants.hpp> // For glm::radians

// if condition is false then it asserts
#define AZ_Assert(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__ \
                      << " in function " << __FUNCTION__ << "\n" \
                      << "Message: " << (msg) << std::endl; \
            std::abort(); \
        } \
    } while (false)

inline const float PIXEL_PER_METER = 100.0f;
inline const uint32_t CHARS_PER_COLLUMNS = 10; // for font atlas
inline const uint32_t CHARS_PER_ROWS= 10; // for font atlas

namespace Az
{

    struct Rect
    {
        glm::vec3 Position = glm::vec3(0.0f);
        glm::vec3 Size = glm::vec3(0.0f);

        // degree
        float rotation = 0.0f;
    };

    float toDegrees(float radian);

    float toRadians(float degree);

    float normalize(float min, float max, float value);

    float deNormalize(float min, float max, float value);

    float getRandomFloat(float min, float max);

    int getRandomInt(int min, int max);

    int getRandomInt(int max);

    void SetWorkingDir();

    float DistanceBetweenPoints(const glm::vec3& p1, const glm::vec3& p2);

    glm::vec3 rotatePoint(glm::vec3 point, glm::vec3 ref, float rad);

    float PixelsToMeters(float pixels);

    float MetersToPixels(float meters);

    void GetTilePosition(int k, int w, int h, int& tileX, int& tileY);

};

