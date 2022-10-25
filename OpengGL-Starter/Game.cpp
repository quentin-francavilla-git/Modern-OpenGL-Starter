#include "Game.h"
#include "ResourceManager.h"

//Constructors & Destructors
Game::Game()
{
    try {
        initWindow();
    }
    catch (runtime_error &error) {
        cerr << error.what() << endl;
    }

    initOpenGL();
    initShader();
    engine = unique_ptr<Engine3D>(new Engine3D());

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

    if (!vtx)
        return;

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
}

//Private Functions
void Game::initShader()
{
    shader = ResourceManager::LoadShader("../shaders/vertex.vs", "../shaders/fragment.fs", nullptr, "shader");

    ResourceManager::GetShader("shader").Use();
    cout << "Shaders loaded." << endl;
}

void Game::initOpenGL()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
        throw runtime_error("Failed to initialize GLEW");
    cout << "Glew init." << endl;


    // OpenGL configuration //
    glViewport(0, 0, windowInfo.windowWidth, windowInfo.windowHeight);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(8);
    glLineWidth(5);
    cout << "OpenGL Configuration." << endl;
}

void Game::initWindow()
{
    //Window data
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
    cout << "Window created." << endl;
}

//Methods
GLFWwindow *Game::getWindow() const
{   
    return _window;
}