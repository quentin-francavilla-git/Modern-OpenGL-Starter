#include "Game.h"
#include "ResourceManager.h"
void Engine2D_Ortho(float left, float right, float bottom, float top, float back, float front);
//Constructors & Destructors
Game::Game()
{
    SWindowInfo windowInfo{};

    windowInfo.res = 1;
    windowInfo.screenWidth = 160 * windowInfo.res;
    windowInfo.screenHeight = 120 * windowInfo.res;
    windowInfo.SW2 = windowInfo.screenWidth / 2;
    windowInfo.SH2 = windowInfo.screenHeight / 2;
    windowInfo.pixelScale = 4 / windowInfo.res;
    windowInfo.windowWidth = windowInfo.screenWidth * windowInfo.pixelScale;
    windowInfo.windowHeight = windowInfo.screenHeight * windowInfo.pixelScale;
    windowInfo.windowTitle = "OpenGL Starter";

    _window = nullptr;

    engine = unique_ptr<Engine3D> (new Engine3D());

    try {
        initWindow(windowInfo);
    }
    catch (runtime_error &error) {
        cerr << error.what() << endl;
    }

    //Shader
    shader = ResourceManager::LoadShader("../shaders/vertex.vs", "../shaders/fragment.fs", nullptr, "shader");

    ResourceManager::GetShader("shader").Use();

}


Game::~Game()
{
}

//Public Functions
void Game::render()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    myVTX *vtx = (myVTX *)malloc(sizeof(myVTX) * 3);

    vtx[0].x = -0.5f;
    vtx[0].y = -0.5f;
    vtx[0].z = 0.0f;

    vtx[1].x = 0.5f;
    vtx[1].y = -0.5f;
    vtx[1].z = 0.0f;

    vtx[2].x = 0.0f;
    vtx[2].y = 0.5f;
    vtx[2].z = 0.0f;



    for (int i = 0; i < 3; i++) {
        vtx[i].r = 1.0f;
        vtx[i].g = 1.5f;
        vtx[i].b = 1.2f;
        vtx[i].a = 1.0f;
    }

    engine->drawPixel(vtx);

    free(vtx);
    //Render here
}

//Private Functions
void Game::initWindow(const SWindowInfo &windowInfo)
{
    if (!glfwInit())
        throw runtime_error("Failed to initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    _window = glfwCreateWindow(windowInfo.windowWidth, windowInfo.windowHeight, windowInfo.windowTitle, NULL, NULL);
    if (!_window)
    {
        throw runtime_error("Failed to open GLFW window.If you have an Intel GPU, they are not 3.3 compatible.Try the 2.1 version of the tutorials.");
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
    glewExperimental = true;

    if (glewInit() != GLEW_OK)
        throw runtime_error("Failed to initialize GLEW");

    // OpenGL configuration //
    // --------------------
    glViewport(0, 0, windowInfo.windowWidth, windowInfo.windowHeight);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(8);
    glLineWidth(5);
}

//Methods
GLFWwindow *Game::getWindow() const
{   
    return _window;
}