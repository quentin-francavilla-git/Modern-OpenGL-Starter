#include "Game.h"
#include "ResourceManager.h"

//Constructors & Destructors
Game::Game()
{
    double lastTime = 0;
    int nbFrames = 0;

    try {
        initWindow();
    }
    catch (runtime_error &error) {
        cerr << error.what() << endl;
    }

    initOpenGL();
    initShader();
    _engine = unique_ptr<Engine3D>(new Engine3D());

}


Game::~Game()
{
}

int tick;
//Public Functions
void Game::render(float deltaTime)
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int size = 1;

    myVTX *vtx = (myVTX *)malloc(sizeof(myVTX) * size);

    if (!vtx)
        return;

    _engine->drawTesting();
    //_engine->drawTriangle(vtx, 3);
    //_engine->drawPixel(vtx);

    free(vtx);
}

void Game::update(float deltaTime)
{
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
    glViewport(0, 0, WindowWidth, WindowHeight);
    glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(pixelScale);
    //glLineWidth(5);
    cout << "OpenGL Configuration." << endl;
}

void Game::initWindow()
{
    if (!glfwInit())
        throw runtime_error("Failed to initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    _window = glfwCreateWindow(WindowWidth, WindowHeight, "Modern OpenGL Starter", NULL, NULL);
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