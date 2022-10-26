#include "Game.h"
#include "ResourceManager.h"

//Constructors & Destructors
Game::Game()
{
    myVTX *vtx = NULL;
    valueXtest = 0;
    valueYtest = 0;
    State = GAME_ACTIVE;

    // Time
    dt = 0.0f;
    currentTime = 0.0f;
    lastTime = 0.0f;
    limitFPS = 1.0 / 60.0;

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

//Public Functions
void Game::render()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    myVTX *vtx = _vtx;

    if (!vtx)
        return;

    //_engine->drawTesting();
    //_engine->drawTriangle(vtx, 3);
    _engine->drawPixel(vtx);

    //free(vtx);
    free(_vtx);
}

void Game::update()
{

    int size = 1;

    _vtx = (myVTX*)malloc(sizeof(myVTX) * size);

    if (!_vtx)
        return;

    _vtx[0].x = valueXtest;
    _vtx[0].y = valueYtest;
    _vtx[0].z = 0.0;

    _vtx[0].r = 1.0;
    _vtx[0].g = 0.0;
    _vtx[0].b = 0.0;
    _vtx[0].a = 1.0;

}

void Game::updateDt()
{
    currentTime = static_cast<float>(glfwGetTime());
    dt = (currentTime - lastTime) / limitFPS;
    lastTime = currentTime;
}

void Game::processInput()
{
    if (State == GAME_ACTIVE)
    {
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cout << "Up" << endl;
            valueYtest += 0.01 * dt;
        }
        else if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cout << "Down" << endl;
            valueYtest -= 0.01 * dt;
        }
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cout << "Left" << endl;
            valueXtest -= 0.01 * dt;
        }
        else if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cout << "Rught" << endl;
            valueXtest += 0.01 * dt;
        }
    }
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

const float &Game::getTime() const
{
    return dt;
}