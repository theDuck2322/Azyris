#pragma once
#include <utils/Types.h>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp> // For glm::rotate
#include <glm/gtc/constants.hpp> // For glm::radians

#define AZ_Assert(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__ \
                      << " in function " << __FUNCTION__ << "\n" \
                      << "Message: " << (msg) << std::endl; \
            std::abort(); \
        } \
    } while (false)

namespace Az
{

    struct Transform
    {
        glm::vec3 Translation = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
        glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 1.0f);
        float Angle = 0;

        inline glm::mat4 getCalculatedModel()
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, Translation);
            model = glm::rotate(model, Angle, Rotation);
            model = glm::scale(model, Scale);

            return model;
        }
    };

    struct Rect
    {
        float x, y;
        float w, h;
    };

    namespace Shapes
    {
        struct Rect
        {
            glm::vec3 Position = glm::vec3(0.0f);
            glm::vec3 Size = glm::vec3(0.0f);

            // degree
            float rotation = 0.0f;
        };
    }

    float toDegrees(float radian);

    float toRadians(float degree);

    float normalize(float min, float max, float value);

    float deNormalize(float min, float max, float value);

    float getRandomFloat(float min, float max);

    int getRandomInt(int min, int max);

    int getRandomInt(int max);

    void SetWorkingDir();

    glm::vec3 rotatePoint(glm::vec3 point, glm::vec3 ref, float rad);

};

