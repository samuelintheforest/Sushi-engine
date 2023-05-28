#include "..\includes\PreNeededInlcudes.h"



#define PI 3.14159265359


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int jid, int event);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
void glfwSetWindowCenter(GLFWwindow* window);


 //Static variables | gloabal variables
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

#include <Windows.h>

//#include "../includes/GameLogic.h"


using namespace sushi;

#ifdef RELEASE_MODE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR     lpCmdLine, int       nShowCmd)
#else
int main()
#endif
{
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    //glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    

    int width = mode->width;
    int height = mode->height;

    width = 1600;
    height = 900;
     
    frameBuffW = width * 0.8f;
    frameBuffH = height;

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, "sushi - Engine", NULL, NULL);
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
    
    

    // === Initialize ImGui editor ===
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
    ImFontConfig fnt_config;
    fnt_config.FontDataOwnedByAtlas = false;
    io.Fonts->AddFontFromMemoryTTF((void*)sushi::fredoka_font_raw, sushi::fredoka_font_size, 15.f, &fnt_config);
 

    // Setup Dear ImGui style
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330 core";
    ImGui_ImplOpenGL3_Init(glsl_version);



    Texture logoTexture(NULL, sushi::fishIconRaw, sushi::fishIonSize, false, NULL, NULL);
    GLFWimage logo;
    
    logo.width = logoTexture.width;
    logo.height = logoTexture.height;
    logo.pixels = logoTexture.data;
    glfwSetWindowIcon(window, 1, &logo);
    logoTexture.deleteTexture();
    logoTexture.freeTexture();

    // Setting pre-gl flags and settings
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glViewport(frameBuffW / 0.8f * 0.2f, 0, frameBuffW, frameBuffH);
    //glEnable(GL_MULTISAMPLE);

    Shader shader("shaders/main.vert", "shaders/main.frag", NULL);
    /*Shader shader3D(".\\shaders\\exp_3d.vert", ".\\shaders\\exp_3d.frag", NULL);
    Shader shader3DMultiDraw(".\\shaders\\exp_multi_draw_3d.vert", ".\\shaders\\exp_multi_draw_3d.frag", NULL);*/

    sushi::SceneDescription world_2d
    {
        sushi::SCENE_2D,
        10,
        sushi::POST_PROCESS_DISABLED
    };

    sushi::SceneDescription world_3d
    {
        sushi::SCENE_3D,
        10,
        sushi::POST_PROCESS_DISABLED
    };

    sushi::SceneDescription world_3d_multi
    {
        sushi::SCENE_3D_MULTI_DRAW,
        10,
        sushi::POST_PROCESS_DISABLED
    };

    //Renderer renderer3D_MultiDraw(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);
    //Renderer* renderer3D_EXP = new Renderer(10000, &shader3DMultiDraw, NULL, NULL, &world_3d_multi);

    int elements = 1000;

    Renderer renderer(elements + 1, &shader, NULL, NULL, &world_2d);

    glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -65535.f, 65535.f);
    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::scale(view, glm::vec3(2.0f, 2.0f, 1.0f));
    renderer.setMatrix(view, proj);


    // === Set up the random number generator =======================
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> random_coordinate_x(0.0f, frameBuffW * 2);
    std::uniform_real_distribution<float> random_coordinate_y(0.0f, frameBuffH * 2);
    std::uniform_real_distribution<float> random_mass(50.0f, 150.0f); // distribution in range [1, 6]
    std::uniform_int_distribution<int> random_color(0, 255); // distribution in range [1, 6]


    // === Set up the Gamepadstate ================================== 
    GLFWgamepadstate state;
    

    // === Predefine some colors ====================================
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
    float dark_blue[3] = { 22.950f,   22.950f,  38.250f };




    // === Set up the physics =======================================
    std::vector<sushi::Physics::Box> boxes;
    int number_of_boxes = elements;
    for (int i = 0; i < number_of_boxes; i++)
    {
        boxes.push_back({glm::vec2((int)random_coordinate_x(rng), (int)random_coordinate_y(rng)), glm::vec2(30, 30), glm::vec3(random_color(rng), random_color(rng), random_color(rng)), glm::vec2(0, 0)});
    }

    b2Vec2 gravity(0.0f, 0.f);
    b2World world(gravity);

  //  std::vector<b2Body*> static_blocks;
  //  for (auto& val : boxes)
  //  {
  //      b2BodyDef bodyDef;
		//bodyDef.type = b2_staticBody;
		//bodyDef.position.Set(val.pos.x, val.pos.y);
  //      b2Body* ground_body = world.CreateBody(&bodyDef);
  //      b2PolygonShape ground_box;
  //      ground_box.SetAsBox(val.size.x / 2.f, val.size.y / 2.f);
  //      ground_body->CreateFixture(&ground_box, 0.f);
		//static_blocks.push_back(ground_body);
  //  }

    
    // === Set up the player ========================================
    sushi::Physics::Box player;
    player.pos = glm::vec2(0.f, 0.f);
    player.size = glm::vec2(30, 30);
    player.color = glm::vec3(white[0], white[1], white[2]);
    //player.color.r = random_color(rng);
    //player.color.g = random_color(rng);
    //player.color.b = random_color(rng);
    player.vel = glm::vec2(0, 0);
    player.prev_pos = player.pos;
    float PLAYER_SPEED = 100;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.pos.x, player.pos.y);
    //bodyDef.linearDamping = 0.1f;

    b2Body* player_body = world.CreateBody(&bodyDef);
    b2PolygonShape player_box;
    player_box.SetAsBox(player.size.x / 2.f, player.size.y / 2.f);
    player_body->SetFixedRotation(true);
    player_body->CreateFixture(&player_box, 0.1f);

    // === Set up the game loop (timestep and important variables) ==
    const float TARGET_FPS = 60.f;
    float physics_fps = 480.f;
    const float FIXED_TIMESTEP = 1.f / physics_fps; // 60 FPS
    const int32 VELOCITY_ITERATIONS = 6;
    const int32 POSITION_ITERATIONS = 2;

    float accumulator = 0.0f;
    float current_time = glfwGetTime();

    // === ImGui states ===
    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //ImGuiStyle& style = ImGui::GetStyle();
    //style.WindowRounding = 5.3f;
    //style.FrameRounding = 2.3f;
    //style.ScrollbarRounding = 0;

    //style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
    //style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    //style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
    //style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
    //style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
    //style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    //style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
    //style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
    //style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
    //style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
    //style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
    //style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
    //style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
    //style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    //style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
    //style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    //style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
    ////style.Colors[ImGuiCol_Combo] = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);
    //style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
    //style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
    //style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
    //style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
    //style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
    //style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
    //style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
    //style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
    //style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
    ////style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    ////style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    ////style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    //style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
    //style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
    //style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    ////style.Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
    ////style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
    ////style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    //style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    //style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    //style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    //style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    //style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    ////style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
    colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Border
    colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
    colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };

    // Text
    colors[ImGuiCol_Text] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
    colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
    colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13, 0.17, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.24, 0.24f, 0.32f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
    colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
    colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
    colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };

    // Docking
    //colors[ImGuiCol_DockingPreview] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };

    auto& style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;


    // Set Up toolbox_window_flags
    ImGuiWindowFlags toolbox_window_flags = 0;
    toolbox_window_flags |= ImGuiWindowFlags_NoCollapse;
    toolbox_window_flags |= ImGuiWindowFlags_NoMove;
    toolbox_window_flags |= ImGuiWindowFlags_NoResize;
    toolbox_window_flags |= ImGuiWindowFlags_NoSavedSettings;
    toolbox_window_flags |= ImGuiWindowFlags_NoNavInputs;


    ImGuiSliderFlags general_settings = 0;
    general_settings |= ImGuiSliderFlags_AlwaysClamp;

    // === Clear the screen =====================================
    renderer.setBackColor(dark_blue[0], dark_blue[1], dark_blue[2], true);

    // === Begin the rendering ==================================
    //renderer.staticBegin();
    //{

    //    // Set the Matrix options
    //    glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -65535.f, 65535.f);
    //    glm::mat4 view = glm::mat4(1.0f);
    //    view = glm::translate(view, glm::vec3((-player.pos.x) + frameBuffW / 2.f - player.size.x, (-player.pos.y) + frameBuffH / 2.f - player.size.y, 0.f));
    //    renderer.setMatrix(view, proj);
    //    //renderer.renderQuadColor(player.pos.x, player.pos.y, player.pos.y, player.size.x, player.size.y, &player.color[0]);

    //    for (int s = 0; s < number_of_boxes; s++)
    //    {
    //        renderer.renderQuadColor((int)boxes[s].pos.x, (int)boxes[s].pos.y, (int)boxes[s].pos.y, boxes[s].size.x, boxes[s].size.y, &boxes[s].color[0]);
    //    }
    //}
    //renderer.staticEnd();
    //renderer.mapMemory();

    // === The game loop ============================================
    while (!glfwWindowShouldClose(window))
    {

        // ##################################################### update ######################################################################################

                // === Update the timers =====================================
        float new_time = glfwGetTime();
        float delta_time = new_time - current_time;
        if (delta_time > 0.25f)
        {
            delta_time = 0.25f;
        }
        current_time = new_time;




        // === Deals with the accumulator ============================
        accumulator += delta_time;



        // === Render the ImGui Layer
                // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            //ImGui::ShowDemoWindow();


            //
            //ImGui::SetNextWindowBgAlpha(0.0f);

            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(((float)frameBuffW / 0.8f) * 0.2f, frameBuffH), ImGuiCond_Always);

            //ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 0.5f);
            ImGui::Begin("Toolbox", 0, toolbox_window_flags);// Create a window called "Hello, world!" and append into it.
            {
                //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                //ImGui::Checkbox("Another Window", &show_another_window);

                //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                //    counter++;
                //ImGui::SameLine();
                //ImGui::Text("counter = %d", counter);

                ImGui::TextWrapped("Time: %.3f ms/frame", 1000.0f / io.Framerate);
                ImGui::Separator();
                ImGui::TextWrapped("FPS: %.1f FPS)", io.Framerate);
                ImGui::Separator();
                ImGui::SliderFloat("Player speed", &PLAYER_SPEED, 50.f, 2000.f, "%.3f", general_settings);


            }
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        //if (show_another_window)
        //{
        //    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //    ImGui::Text("Hello from another window!");
        //    if (ImGui::Button("Close Me"))
        //        show_another_window = false;
        //    ImGui::End();
        //}

        // === Imgui Rendering ===
        ImGui::Render();



        while (accumulator >= FIXED_TIMESTEP)
        {
            // Poll input events and other events
            processInput(window);
            glfwPollEvents();

            // handle user input
            float horizontalVelocity = 0.0f;
            float verticalVelocity = 0.0f;
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                horizontalVelocity -= 1.0f;
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                horizontalVelocity += 1.0f;
            }
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                verticalVelocity -= 1.0f;
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                verticalVelocity += 1.0f;
            }

            if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
            {
                if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP])
                {
                    verticalVelocity -= 1.0f;
                }
                if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN])
                {
                    verticalVelocity += 1.0f;
                }
                if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT])
                {
                    horizontalVelocity -= 1.0f;
                }
                if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT])
                {
                    horizontalVelocity += 1.0f;
                }
            }
            // normalize diagonal movement
            if (horizontalVelocity != 0.0f && verticalVelocity != 0.0f)
            {
                float magnitude = std::sqrt(horizontalVelocity * horizontalVelocity + verticalVelocity * verticalVelocity);
                horizontalVelocity /= magnitude;
                verticalVelocity /= magnitude;
            }

            // apply user input to player's Box2D body
            b2Vec2 velocity = b2Vec2(horizontalVelocity * PLAYER_SPEED, verticalVelocity * PLAYER_SPEED);
            player_body->SetLinearVelocity(velocity);

            // update Box2D world with fixed timestep
            world.Step(FIXED_TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

            // iterate over Box2D bodies and update their game objects
            b2Vec2 position = player_body->GetPosition();
            player.pos = glm::vec2(position.x, position.y);
            player.prev_pos = glm::vec2(player_body->GetPosition().x, player_body->GetPosition().y);





            accumulator -= FIXED_TIMESTEP;
        }

        // Setting the alpa variable (value between 0 an 1)
        float alpha = accumulator / FIXED_TIMESTEP;

        // interpolate game object's position between current and previous state
        b2Vec2 position = player_body->GetPosition();
        b2Vec2 previousPosition = b2Vec2(player.prev_pos.x, player.prev_pos.y);
        b2Vec2 interpolatedPosition = alpha * position + (1 - alpha) * previousPosition;
        player.pos = glm::vec2(interpolatedPosition.x, interpolatedPosition.y);
        

        // ############################ rendering ###################################


        

        //// === Clear the screen =====================================
        renderer.setBackColor(dark_blue[0], dark_blue[1], dark_blue[2], true);
        /*renderer.satic_render();*/
        // === Begin the rendering ==================================
        renderer.begin();
        {

            // Set the Matrix options
            glm::mat4 proj = glm::orthoRH(0.0f, (float)frameBuffW, (float)frameBuffH, 0.0f, -65535.f, 65535.f);
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3((- player.pos.x) + frameBuffW / 2.f - player.size.x, (- player.pos.y) + frameBuffH / 2.f - player.size.y, 0.f));
            renderer.setMatrix(view, proj);



            renderer.renderQuadColor(player.pos.x, player.pos.y, player.pos.y, player.size.x, player.size.y, &player.color[0]);
            for (int s = 0; s < elements; s++)
            {
                renderer.renderQuadColor((int)boxes[s].pos.x, (int)boxes[s].pos.y, (int)boxes[s].pos.y, boxes[s].size.x, boxes[s].size.y, &boxes[s].color[0]);
            }
        }
        renderer.end();
        


        // === Swap the buffers =====================================
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glFinish();
        //glFlush();
        //double sleep_time = (1.0 / TARGET_FPS) - delta_time;
        //if (sleep_time > 0.0)
        //{
        //    std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
        //}
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));


    } // end of game loop

    
    // Cleaning up
    // ------------------------------------------------------------------
    // de-allocate all resources once they've outlived their purpose:

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    renderer.destroy();


    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "DEBUG:: POROGRAM NOW TERMINATES!\nAll RESOURCES HAVE BEEN DEALLOCATED FROM MEMORY" << std::endl;
    //using namespace std::chrono_literals;
    ///*Display *display = new Display(800, 800, false, false);*/
    //GameLogic::initGame();
    ////std::this_thread::sleep_for(2000ms);
    ////GameLogic::DisplayManager->enableWindowFullscreen();
    ////std::this_thread::sleep_for(10000ms);
    ////GameLogic::DisplayManager->disableWindowFullscreen();
    ////std::this_thread::sleep_for(10000ms);
    //while (!GameLogic::DisplayManager->getWindowShouldClose())
    //{
    //    GameLogic::InputManager->pollEvents();
    //    glClearColor(0.19608f, 0.65882f, 0.32157f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glfwSwapBuffers(GameLogic::DisplayManager->window);
    //}
    //GameLogic::endGame();
    //delete display;

    return 0;
}

 //process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
 //---------------------------------------------------------------------------------------------------------
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
    //std::cout << width << ", " << height << std::endl;
    frameBuffW = width * 0.8;
    frameBuffH = height;
    
    glViewport(frameBuffW / 0.8f * 0.2f, 0, frameBuffW, frameBuffH);

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

