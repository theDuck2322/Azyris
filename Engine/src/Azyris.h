#pragma once

#include <glad/glad.h>

#include <Chipmunk2D/chipmunk/chipmunk.h>


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // Include for glm::value_ptr
#include <glm/gtx/string_cast.hpp>



#include <iostream>
#include <windows.h>
#include <typeinfo>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <AzyrisKeys.h>

#include <buffers/VBO.h>
#include <buffers/EBO.h>
#include <buffers/VAO.h>



#include <core/Window.h>
#include <core/Input.h>

#include <physics/CP_Scene.h>
#include <physics/CP_BoxCollider.h>

#include <Renderer/Renderer.h>

#include <Renderer/Camera2D.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>


#include <utils/Timer.h>
#include <utils/Helpers.h>
#include <utils/Types.h>

inline float SCREEN_WIDTH = 1280;
inline float SCREEN_HEIGHT = 720;

