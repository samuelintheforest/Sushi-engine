#pragma once
#ifndef PRE_NEEDED_INCLUDES
#define PRE_NEEDED_INCLUDES

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "RawSrc.h"

#include <iostream>

#include <thread>
#include <chrono>
#include <algorithm>    
#include <random>
#include <vector>
#include <cstring>
#include <cmath>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Physics.h"
#include "Scene.h"

#endif // !PRE_NEEDED_INCLUDES

