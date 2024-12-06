#include "GameLogic.h"
#include "Rectangle.h"
#include "Layer.h"
#include "FilledRectColorFix.h"
#include "Types.h"

using namespace sushi;

int main()
{
	IVec3 green = { 99, 219, 105 };
	IVec3 purple = { 102, 3, 252 };
	GameLogic::initGame();


	FilledRectColorFix rect_green = { { 1, 1, 303, 130 }, { green, 255 }, 1 };
	FilledRectColorFix rect_blue = { { 150, 70, 303, 130 }, { purple, 255 }, 0 };

	GameLogic::GraphicsManager->setUpSGXVertexMisc();
	while(!GameLogic::DisplayManager->getWindowShouldClose())
	{
		/* Poll the events, update state */
		GameLogic::updateState();

		std::cout << "Ellapsed time since startup: " << GameLogic::TimerManager->getTimeMicroSec() << std::endl;
		/* Main logic */
		/* TODO */
		GameLogic::renderState();
	}

	GameLogic::endGame();
}

//// HELPER FUNCTION: CENTERS THE SCREEN
//void glfwSetWindowCenter(GLFWwindow* window) {
//    // Get window position and size
//    int window_x, window_y;
//    glfwGetWindowPos(window, &window_x, &window_y);
//
//    int window_width, window_height;
//    glfwGetWindowSize(window, &window_width, &window_height);
//
//    // Halve the window size and use it to adjust the window position to the center of the window
//    window_width *= 0.5;
//    window_height *= 0.5;
//
//    window_x += window_width;
//    window_y += window_height;
//
//    // Get the list of monitors
//    int monitors_length;
//    GLFWmonitor** monitors = glfwGetMonitors(&monitors_length);
//
//    if (monitors == NULL) {
//        // Got no monitors back
//        return;
//    }
//
//    // Figure out which monitor the window is in
//    GLFWmonitor* owner = NULL;
//    int owner_x, owner_y, owner_width, owner_height;
//
//    for (int i = 0; i < monitors_length; i++) {
//        // Get the monitor position
//        int monitor_x, monitor_y;
//        glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);
//
//        // Get the monitor size from its video mode
//        int monitor_width, monitor_height;
//        GLFWvidmode* monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);
//
//        if (monitor_vidmode == NULL) {
//            // Video mode is required for width and height, so skip this monitor
//            continue;
//
//        }
//        else {
//            monitor_width = monitor_vidmode->width;
//            monitor_height = monitor_vidmode->height;
//        }
//
//        // Set the owner to this monitor if the center of the window is within its bounding box
//        if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
//            owner = monitors[i];
//
//            owner_x = monitor_x;
//            owner_y = monitor_y;
//
//            owner_width = monitor_width;
//            owner_height = monitor_height;
//        }
//    }
//
//    if (owner != NULL) {
//        // Set the window position to the center of the owner monitor
//        glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
//    }
//}
//
//
///*
//
//
////    // glfw: initialize and configure
////    // ------------------------------
////
////    glfwInit();
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
////    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
////
////    GLFWmonitor* primary = glfwGetPrimaryMonitor();
////    const GLFWvidmode* mode = glfwGetVideoMode(primary);
////
////
////    int width = mode->width;
////    int height = mode->height;
////
////    //width = 1600;
////    //height = 900;
////
////    frameBuffW = width;
////    frameBuffH = height;
////
////    // glfw window creation
////    // --------------------
////    GLFWwindow* window = glfwCreateWindow(width, height, "sushi - Engine", primary, NULL);
////    if (window == NULL)
////    {
////        std::cout << "Failed to create GLFW window" << std::endl;
////        glfwTerminate();
////        return -1;
////    }
////
////    glfwMakeContextCurrent(window);
////    glfwSwapInterval(1); // Enable V-Sync
////    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
////    glfwSetCursorPosCallback(window, cursor_position_callback);
////    glfwSetScrollCallback(window, scroll_callback);
////    glfwSetJoystickCallback(joystick_callback);
////    glfwSetMouseButtonCallback(window, mouse_button_callback);
////    glfwSetWindowCenter(window);
////
////    // glad: load all OpenGL function pointers
////// ---------------------------------------
////    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
////    {
////        std::cout << "Failed to initialize GLAD" << std::endl;
////        return -1;
////    }
////
////
////
////
////    Texture logoTexture(NULL, sushi::fishIconRaw, sushi::fishIonSize, false, NULL, NULL);
////    GLFWimage logo;
////
////    logo.width = logoTexture.width;
////    logo.height = logoTexture.height;
////    logo.pixels = logoTexture.data;
////    glfwSetWindowIcon(window, 1, &logo);
////    logoTexture.deleteTexture();
////    logoTexture.freeTexture();
//
//    // Setting pre-gl flags and settings
//    glEnable(GL_BLEND);
//    glEnable(GL_DEPTH_TEST);
//    glViewport(0, 0, frameBuffW, frameBuffH);
//    //glEnable(GL_MULTISAMPLE);
//
//    //Shader shader("shaders/main.vert", "shaders/main.frag", NULL);
//    ///*Shader shader3D(".\\shaders\\exp_3d.vert", ".\\shaders\\exp_3d.frag", NULL);
//    //Shader shader3DMultiDraw(".\\shaders\\exp_multi_draw_3d.vert", ".\\shaders\\exp_multi_draw_3d.frag", NULL);*/
//
//    //sushi::SceneDescription world_2d
//    //{
//    //    sushi::SCENE_2D,
//    //    10,
//    //    sushi::POST_PROCESS_DISABLED
//    //};
//
//    //sushi::SceneDescription world_3d
//    //{
//    //    sushi::SCENE_3D,
//    //    10,
//    //    sushi::POST_PROCESS_DISABLED
//    //};
//
//    //sushi::SceneDescription world_3d_multi
//    //{
//    //    sushi::SCENE_3D_MULTI_DRAW,
//    //    10,
//    //    sushi::POST_PROCESS_DISABLED
//    //};
//
//    //Renderer renderer3D_MultiDraw(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);
//    //Renderer* renderer3D_EXP = new Renderer(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);
//
//    //int elements = 1000;
//
//    //Renderer renderer(elements + 1, &shader, NULL, NULL, &world_2d);
//
//    //glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -65535.f, 65535.f);
//    //glm::mat4 view = glm::mat4(1.0f);
//    ////view = glm::scale(view, glm::vec3(2.0f, 2.0f, 1.0f));
//    //renderer.setMatrix(view, proj);
//
//
//    //// === Set up the random number generator =======================
//    //std::random_device dev;
//    //std::mt19937 rng(dev());
//    //std::uniform_real_distribution<float> random_coordinate_x(0.0f, frameBuffW * 2);
//    //std::uniform_real_distribution<float> random_coordinate_y(0.0f, frameBuffH * 2);
//    //std::uniform_real_distribution<float> random_mass(50.0f, 150.0f); // distribution in range [1, 6]
//    //std::uniform_int_distribution<int> random_color(0, 255); // distribution in range [1, 6]
//
//
//    //// === Set up the Gamepadstate ================================== 
//    //GLFWgamepadstate state;
//
//
//    //// === Predefine some colors ====================================
//    //float red[] = { 255, 0, 0 };
//    //float white[] = { 255 ,255 ,255 };
//    //float black[] = { 0, 0, 0 };
//    //float blue[] = { 0, 0, 255 };
//    //float green[] = { 0 , 255 , 0 };
//    //float turquoise[] = { 74, 240, 179 };
//    //float orange[] = { 235, 125, 52 };
//    //float yellow[] = { 255, 255, 0 };
//    //float grey[] = { 133, 133, 133 };
//    //float purple[] = { 87, 84, 255 };
//    //float sand[] = { 235, 201, 52 };
//    //float dark_blue[3] = { 22.950f,   22.950f,  38.250f };
//
//
//
//
//    // //=== Set up the physics =======================================
//    //std::vector<sushi::Physics::Box> boxes;
//    //int number_of_boxes = elements;
//    //for (int i = 0; i < number_of_boxes; i++)
//    //{
//    //    boxes.push_back({glm::vec2((int)random_coordinate_x(rng), (int)random_coordinate_y(rng)), glm::vec2(30, 30), glm::vec3(random_color(rng), random_color(rng), random_color(rng)), glm::vec2(0, 0)});
//    //}
//
//
//
//    //// === Set up the player ========================================
//    //sushi::Physics::Box player;
//    //player.pos = glm::vec2(0.f, 0.f);
//    //player.size = glm::vec2(30, 30);
//    //player.color = glm::vec3(sand[0], sand[1], sand[2]);
//    ////player.color.r = random_color(rng);
//    ////player.color.g = random_color(rng);
//    ////player.color.b = random_color(rng);
//    //player.vel = glm::vec2(0, 0);
//    //player.prev_pos = player.pos;
//    //float PLAYER_SPEED = 1000;
//    //float new_time = glfwGetTime();
//    //float delta_time = new_time;
//    //// === Set up the game loop (timestep and important variables) ==
//    //const float TARGET_FPS = 60.f;
//    //float physics_fps = 480.f;
//    //const float FIXED_TIMESTEP = 1.f / physics_fps; // 60 FPS
//    //const int32_t VELOCITY_ITERATIONS = 6;
//    //const int32_t POSITION_ITERATIONS = 2;
//
//    //float accumulator = 0.0f;
//    //float current_time = glfwGetTime();
//
//    //// === Clear the screen =====================================
//    //renderer.setBackColor(black[0], black[1], black[2], true);
//
///*
//    // === The game loop ============================================
//while (!glfwWindowShouldClose(window))
//{
//
//    // ##################################################### update ######################################################################################
//
//    // === Update the timers =====================================
//    delta_time = glfwGetTime() - new_time;
//    new_time = glfwGetTime();
//
//    processInput(window);
//    glfwPollEvents();
//
//    // handle user input
//    float horizontalVelocity = 0.0f;
//    float verticalVelocity = 0.0f;
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//    {
//        horizontalVelocity -= 1.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//    {
//        horizontalVelocity += 1.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//    {
//        verticalVelocity -= 1.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//    {
//        verticalVelocity += 1.0f;
//    }
//
//    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
//    {
//        if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP])
//        {
//            verticalVelocity -= 1.0f;
//        }
//        if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN])
//        {
//            verticalVelocity += 1.0f;
//        }
//        if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT])
//        {
//            horizontalVelocity -= 1.0f;
//        }
//        if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT])
//        {
//            horizontalVelocity += 1.0f;
//        }
//    }
//    // normalize diagonal movement
//    if (horizontalVelocity != 0.0f && verticalVelocity != 0.0f)
//    {
//        float magnitude = std::sqrt(horizontalVelocity * horizontalVelocity + verticalVelocity * verticalVelocity);
//        horizontalVelocity /= magnitude;
//        verticalVelocity /= magnitude;
//    }
//
//    horizontalVelocity *= PLAYER_SPEED;
//    verticalVelocity *= PLAYER_SPEED;
//
//    player.pos.x += horizontalVelocity * delta_time;
//    player.pos.y += verticalVelocity * delta_time;
//
//
//
//    //// === Clear the screen =====================================
//    renderer.setBackColor(dark_blue[0], dark_blue[1], dark_blue[2], true);
//    /*renderer.satic_render();*/
//    // === Begin the rendering ==================================
//
//
//    renderer.begin();
//    {
//
//        // Set the Matrix options
//        glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -65535.f, 65535.f);
//        glm::mat4 view = glm::mat4(1.0f);
//        view = glm::translate(view, glm::vec3((-player.pos.x) + frameBuffW / 2.f - player.size.x, (-player.pos.y) + frameBuffH / 2.f - player.size.y, 0.f));
//        renderer.setMatrix(view, proj);
//
//
//
//        renderer.renderQuadColor(player.pos.x, player.pos.y, player.pos.y, player.size.x, player.size.y, &player.color[0]);
//        for (int s = 0; s < elements; s++)
//        {
//            renderer.renderQuadColor((int)boxes[s].pos.x, (int)boxes[s].pos.y, (int)boxes[s].pos.y, boxes[s].size.x, boxes[s].size.y, &boxes[s].color[0]);
//        }
//    }
//    renderer.end();
//
//
//
//    // === Swap the buffers =====================================
//    glfwSwapBuffers(window);
//    glFinish();
//}
//
//renderer.destroy();
//
//
//glfwDestroyWindow(window);
//glfwTerminate();
//
//std::cout << "DEBUG:: POROGRAM NOW TERMINATES!\nAll RESOURCES HAVE BEEN DEALLOCATED FROM MEMORY" << std::endl;
//
//return 0;
//
//*/