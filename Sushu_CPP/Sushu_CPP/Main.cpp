#include "PreNeededInlcudes.h"

using namespace Sushi;

#define PI 3.14159265359


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int jid, int event);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
void glfwSetWindowCenter(GLFWwindow* window);


// Static variables | gloabal variables
unsigned short frameBuffW;
unsigned short frameBuffH;

short m_posx = 0;
short m_posy = 0;
double prev_mposX = m_posx;
double prev_mposY = m_posy;
double d_mposx = 0;
double d_mposy = 0;
double prev_d_mposx = 0;
double prev_d_mposy = 0;
double topMY = 0;
double biggestTop = 0;
double offset = 0;

bool leftClick = false;
bool rightClick = false;
int cameraTop = 0;

float camera_zoom= 1.0f;




#ifdef RELEASE_MODE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR     lpCmdLine, int       nShowCmd)
#else
int main()
#endif
{
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    //glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    //glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    

    int width = mode->width;
    int height = mode->height;

    width = 1280;
    height = 720;

    frameBuffW = width;
    frameBuffH = height;

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width-3, height-3, "Sushi - Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetJoystickCallback(joystick_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowCenter(window);

    // glad: load all OpenGL function pointers
// ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    Texture logoTexture(NULL, Sushi::fishIconRaw, Sushi::fishIonSize, false, NULL, NULL);
    GLFWimage logo;
    
    logo.width = logoTexture.width;
    logo.height = logoTexture.height;
    logo.pixels = logoTexture.data;
    glfwSetWindowIcon(window, 1, &logo);
    logoTexture.deleteTexture();
    logoTexture.freeTexture();

    // Setting pre-gl flags and settings
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, frameBuffW, frameBuffH);
    //glEnable(GL_MULTISAMPLE);

    Shader shader(".\\shaders\\main.vert", ".\\shaders\\main.frag", NULL);
    Shader shader3D(".\\shaders\\exp_3d.vert", ".\\shaders\\exp_3d.frag", NULL);
    Shader shader3DMultiDraw(".\\shaders\\exp_multi_draw_3d.vert", ".\\shaders\\exp_multi_draw_3d.frag", NULL);

    Scene::SceneDescription world_2d
    {
        Scene::SCENE_2D,
        10,
        Scene::POST_PROCESS_DISABLED
    };

    Scene::SceneDescription world_3d
    {
        Scene::SCENE_3D,
        10,
        Scene::POST_PROCESS_DISABLED
    };

    Scene::SceneDescription world_3d_multi
    {
        Scene::SCENE_3D_MULTI_DRAW,
        10,
        Scene::POST_PROCESS_DISABLED
    };

    

    



    //Renderer renderer3D_MultiDraw(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);
    Renderer* renderer3D_EXP = new Renderer(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);
    //Renderer renderer(100, &shader, NULL, NULL, &world_2d);

    glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -1.f, 1.f);
    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::scale(view, glm::vec3(2.0f, 2.0f, 1.0f));
    //renderer.setMatrix(view, proj);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> random_coordinate_x(0.0f, frameBuffW);
    std::uniform_real_distribution<float> random_coordinate_y(0.0f, frameBuffH);
    std::uniform_real_distribution<float> random_mass(50.0f, 150.0f); // distribution in range [1, 6]
    std::uniform_int_distribution<int> random_color(0, 255); // distribution in range [1, 6]

    //std::vector<float> quad_colors;

    //int gridRowL = 90;
    //int gridColumnL = 60;
   

    /*std::cout << quadData.size() << std::endl;*/

    /*for (int i = 0; i < quadData.size(); i++)
    {
        std::cout << quadData[i].x << ", " << quadData[i].y << std::endl;
    }*/

    GLFWgamepadstate state;
    
    //renderer.setBackColor(255, 255, 255, false);

    float fps = 60.0f;
    float temp[3];
    
    int frameNum = 0;

    //double m_xpos;
    //double m_ypos;
    /*GLsync fence;
    float lastTime = 1.0f;

    float beginingOfFrame = glfwGetTime();


    const int FRAMES_PER_SECOND = 30;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

    DWORD next_game_tick = GetTickCount64();

    int sleep_time = 0;*/

    // Variables to create periodic event for FPS displaying
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    // Keeps track of the amount of frames in timeDiff
    unsigned int counter = 0;
    double lasttime = glfwGetTime();

    float startFrame = glfwGetTime();
    float endFrame = glfwGetTime();
    float dt = endFrame - startFrame;
    glm::vec2 playerPos(width / 2, height / 2);
    glm::vec2 direction(0, 0);
    double t = 0.0;

    double currentTime = glfwGetTime();

    // --- ONLY FOR NOT WORKING PHYSICS! ----------------------------
    //Physics::Box playerBox{
    //   glm::vec2(280, 100),
    //   glm::vec2(15, 15)
    //};
    // --------------------------------------------------------------

    float red[] = { 255, 0, 0 };
    float white[] = { 255 ,255 ,255 };
    float black[] = { 0, 0, 0 };
    float blue[] = { 0, 0, 255 };
    float green[] = { 0 , 255 , 0 };
    float turquoise[] = { 74, 240, 179 };
    float orange[] = { 235, 125, 52 };
    float yellow[] = { 255, 255, 0 };
    float grey[] = { 133, 133, 133 };
    float purple[] = { 87, 84, 255 };
    float sand[] = { 235, 201, 52 };

    //glLineWidth(5.f);
    //glPointSize(4.f);
    //glEnable(GL_MULTISAMPLE);

    // --- ONLY FOR NOT WORKING PHYSICS! ----------------------------
    //std::vector<int> collidedBoxes;
    //std::vector<std::pair<int, float>> z;
    // --------------------------------------------------------------
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //std::vector<Physics::Mover> movers;
    //for (int i = 0; i < 10; i++)
    //{
    //    movers.push_back(Physics::Mover((float)random_coordinate_x(rng), random_coordinate_y(rng), random_mass(rng)));
    //}

    Sushi::Physics::Box player;
    player.pos = glm::vec2(0.f, 0.f);
    player.size = glm::vec2(50, 50);
    player.color = glm::vec3(white[0], white[1], white[2]);
    player.vel = glm::vec2(0, 0);
    int SPEED = 10;
    
    glm::vec2 flat_stuff = glm::vec2(0.f, 0.f);
    double y = 0;
    glm::vec2 prev_flat_vec = glm::vec2(0.f, 0.f);
    double prev_y = 0;
    double length = 0;
    double prev_length = 0;


    glfwSetWindowCenter(window);


    while (!glfwWindowShouldClose(window))
    {
        
       

// ##################################################### update ######################################################################################

        //std::cout << dt << std::endl;
        startFrame = glfwGetTime();

        // Measuring FPS and 1 frame time (in ms)
        //crntTime = glfwGetTime();
        //timeDiff = crntTime - prevTime;
        //counter++;

        //if (timeDiff >= 1.0f / 16.0f)
        //{

        //    std::string FPS = std::to_string((int)((1.0f / timeDiff) * counter));
        //    std::string ms = std::to_string((timeDiff / counter) * 1000.f);
        //    std::string newTitle = "Sushi - Engine | " + FPS + "FPS / " + ms + "ms";
        //    glfwSetWindowTitle(window, newTitle.c_str()); // Creates new title name


        //    prevTime = crntTime;
        //    counter = 0;

        //}

        // Poll input events and other events
        processInput(window);
        glfwPollEvents();
        
        player.vel = { 0.f , 0.f };

        // Getting keyboard input
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            player.vel.y -= SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            player.vel.y += SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            player.vel.x -= SPEED;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            player.vel.x += SPEED;
        }

        //player.vel += glm::vec2(0.0f, 1.2f);

        glm::normalize(player.vel);
        //std::cout << player.vel.x << " " << player.vel.y << std::endl;
        player.pos.x += player.vel.x * dt;
        player.pos.y += player.vel.y * dt;

        

// ################################################################# rendering ###############################x###################################


        renderer3D_EXP->setBackColor(0, 0, 0, true);
        //renderer3D_EXP.setBackColor(orange[0], orange[1], orange[2], true);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)frameBuffW / (float)frameBuffH, 0.1f, 10000.0f);
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        float radius = 20.0f * camera_zoom;
        flat_stuff = glm::vec2(cos(glm::radians(d_mposx)) * radius, sin(glm::radians(d_mposx)) * radius);
        flat_stuff *= cos(glm::radians(d_mposy));
        y = sin(glm::radians(d_mposy)) * radius;
        length = sqrtf(flat_stuff.x * flat_stuff.x + flat_stuff.y * flat_stuff.y);
        view = glm::lookAt(glm::vec3(flat_stuff.x, y, flat_stuff.y), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(player.pos.x, 0.f, player.pos.y));
        

        renderer3D_EXP->setModelMatrix(model, view, projection);
        renderer3D_EXP->shader->use();
        renderer3D_EXP->shader->setFloat("time", glfwGetTime());

        renderer3D_EXP->draw3d_EXP_Multi();

        // Swaping buffer and tell Opengl to finish earlier
        glfwSwapBuffers(window);
        //glFinish();
        glFlush();
        dt = glfwGetTime() - startFrame;
        /*long to_sleep = 16666667 - (dt * (1000000000));
        std::this_thread::sleep_for(std::chrono::nanoseconds(to_sleep));*/


    } // end of game loop

    
    // Cleaning up
    // ------------------------------------------------------------------
    // de-allocate all resources once they've outlived their purpose:

    renderer3D_EXP->destroy();
    delete renderer3D_EXP;
    glfwTerminate();

    std::cout << "DEBUG:: POROGRAM NOW TERMINATES!\nAll RESOURCES HAVE BEEN DEALLOCATED FROM MEMORY" << std::endl;

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    //std::cout << width << ", " << height << std::endl;
    frameBuffW = width;
    frameBuffH = height;
    //glfwSetWindowCenter(window);
    glfwSwapBuffers(window);
}

// MOUSE POSITION CALLBACK
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    m_posx = xpos;
    m_posy = ypos;


    if ((d_mposy >= 90.0f && cameraTop == 0) || (d_mposy <= -90.0f && cameraTop == 0))
    {
        topMY = m_posy;
        cameraTop = 1;
    } 
    else if ((d_mposy < 90.f && d_mposy > -90.f) && cameraTop != 0)
    {
        cameraTop = 0;
        //biggestTop = 0;
    }

    if (cameraTop == 1 && leftClick)
    {
        //std::cout << m_posy - topMY << std::endl;
        //if (biggestTop <= (m_posy - topMY) )
        //{
        //    std::cout << "nagyobb!" << std::endl;
        //    biggestTop = (m_posy - topMY);
        //    offset = biggestTop;
        //}
        //else if (biggestTop > (m_posy - topMY))
        //{
        //    biggestTop = 0;
        //    cameraTop = 0;
        //    m_posx -= offset;
        //    std::cout << "kisebb!    " << (m_posy - topMY) <<  std::endl;
        //    /*std::cout << biggestTop << std::endl;
        //    *///m_posx = biggestTop;

        //    //m_posx = topMY;
        //}
    }


    if (leftClick)
    {

        d_mposx = ((m_posx - prev_mposX) * 0.3 + prev_d_mposx);
        d_mposy = ((m_posy - prev_mposY) * 0.3 + prev_d_mposy);
    }
    
    if (d_mposy >= 90.0f)
    {
        d_mposy = 90.0f;
    }
    else if (d_mposy <= -90.0f)
    {
        d_mposy = -90.0f;
    }

    //std::cout << m_posx << ", " << m_posy << std::endl;
}



// MOUSE SCROLL CALLBACK
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera_zoom += (yoffset * 0.1f);


    if (camera_zoom <= 0.05f)
    {
        camera_zoom = 0.05f;
    }
}

// MOUSE BUTTON CALLBACK
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {       
        leftClick = true;
        prev_mposX = m_posx;
        prev_mposY = m_posy;
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        leftClick = false;

        prev_d_mposx = d_mposx;
        prev_d_mposy = d_mposy;
    }
    
}

// Controller and Joystick connection disconection callback
void joystick_callback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
    {
        std::cout << "DEBUG:: Joystick connected!\n" << "Joystick ID: " << jid << std::endl;
        if (glfwJoystickIsGamepad(jid)) 
        {
            std::cout << glfwGetGamepadName(jid) << std::endl;
        }

        // The joystick was connected
    }
    else if (event == GLFW_DISCONNECTED)
    {

        std::cout << "DEBUG:: Joystick disconnected!\n" << "Joystick ID: " << jid << std::endl;
        // The joystick was disconnected
    }
}


// HELPER FUNCTION: CENTERS THE SCREEN
void glfwSetWindowCenter(GLFWwindow* window) {
    // Get window position and size
    int window_x, window_y;
    glfwGetWindowPos(window, &window_x, &window_y);

    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // Halve the window size and use it to adjust the window position to the center of the window
    window_width *= 0.5;
    window_height *= 0.5;

    window_x += window_width;
    window_y += window_height;

    // Get the list of monitors
    int monitors_length;
    GLFWmonitor** monitors = glfwGetMonitors(&monitors_length);

    if (monitors == NULL) {
        // Got no monitors back
        return;
    }

    // Figure out which monitor the window is in
    GLFWmonitor* owner = NULL;
    int owner_x, owner_y, owner_width, owner_height;

    for (int i = 0; i < monitors_length; i++) {
        // Get the monitor position
        int monitor_x, monitor_y;
        glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

        // Get the monitor size from its video mode
        int monitor_width, monitor_height;
        GLFWvidmode* monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);

        if (monitor_vidmode == NULL) {
            // Video mode is required for width and height, so skip this monitor
            continue;

        }
        else {
            monitor_width = monitor_vidmode->width;
            monitor_height = monitor_vidmode->height;
        }

        // Set the owner to this monitor if the center of the window is within its bounding box
        if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
            owner = monitors[i];

            owner_x = monitor_x;
            owner_y = monitor_y;

            owner_width = monitor_width;
            owner_height = monitor_height;
        }
    }

    if (owner != NULL) {
        // Set the window position to the center of the owner monitor
        glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
    }
}



// Render 2d graphics
        //renderer.begin();
        //{
        //    renderer.setBackColor(grey[0], grey[1], grey[2], false);
        //    shader.use();
        //    shader.setFloat("iTime", glfwGetTime());
        //    // Set the shader uniform matrices
        //    proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -1.f, 1.f);
        //    view = glm::mat4(1.0f);
        //    view = glm::scale(view, glm::vec3(camera_zoom, camera_zoom, 1.0f));
        //    renderer.setMatrix(view, proj);

        //    

        //    renderer.renderQuadColor(player.pos.x, player.pos.y, 0, player.size.x, player.size.y, &player.color[0]);

        //    //renderer->renderQuadColor(playerBox.pos.x, playerBox.pos.y, 1, 12, 12, blue);

        //    //renderer->renderQuadColor(broadphasebox.pos.x, broadphasebox.pos.y, -1, broadphasebox.size.x, broadphasebox.size.y, red);
        //    //renderer.renderQuadColor(objPosX, objPosY, 0, 40, 40, white);
        //    
        //    /*for (int i = 0; i < 10; i++)
        //    {
        //        renderer.renderQuadColor(movers[i].pos.x, movers[i].pos.y, 0, movers[i].size * 2, movers[i].size * 2, orange);
        //    }
        //    renderer.renderQuadColor(attractor.pos.x, attractor.pos.y, 0, attractor.size * 2, attractor.size * 2, white);*/

        //    //renderer.renderQuadColor(10.f, 10.f, 1, 200.0f, 200.0f, purple);
        //    //renderer->renderQuadColor(vMouse.x, vMouse.y, 15, 12, 12, black);
        //    /*for (int i = 0; i < playerBox.contact.size(); i++) {
        //        renderer->renderQuadColor(playerBox.contact[i]->pos.x, playerBox.contact[i]->pos.x, 1, playerBox.contact[i]->size.x, playerBox.contact[i]->size.x, red);
        //    }*/

        //    //for (int i = 0; i < vRects.size(); i++)
        //    //{
        //    //    /*if (collidedBoxes[i] != -1)
        //    //    {
        //    //        renderer->renderQuadColor(vRects[i].pos.x, vRects[i].pos.y, 0, vRects[i].size.x, vRects[i].size.y, red);
        //    //    }
        //    //    else
        //    //    {*/
        //    //        renderer.renderQuadColor(vRects[i].pos.x, vRects[i].pos.y, 0, vRects[i].size.x, vRects[i].size.y, turquoise);
        //    //    //}
        //    //        /*for (int j = 0; j < vRects[i].contact.size(); j++) {
        //    //            renderer->renderQuadColor(vRects[i].contact[j]->pos.x, vRects[i].contact[j]->pos.x, 1, vRects[i].contact[j]->size.x, vRects[i].contact[j]->size.x, red);
        //    //        }*/
        //    //}

        //}
        //renderer.end();

