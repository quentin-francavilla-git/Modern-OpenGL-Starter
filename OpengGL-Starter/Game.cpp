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
    _engine = unique_ptr<Engine3D>(new Engine3D());

}


Game::~Game()
{
}

int tick;
//Public Functions
void Game::render()
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int size = 1;

    myVTX *vtx = (myVTX *)malloc(sizeof(myVTX) * size);

    if (!vtx)
        return;
    float x, y, c = 0;
    for (y = 0; y < ScreenHeight2; y++)
    {
        for (x = 0; x < ScreenWidth2; x++)
        {
            vtx[0].x = x * (pixelScale / 2);
            vtx[0].y = y * (pixelScale / 2);
            vtx[0].z = 0.0;

            vtx[0].x /= ScreenWidth;
            vtx[0].y /= ScreenHeight;

            if (c == 0) { vtx[0].r = 255/255; vtx[0].g = 255 / 255; vtx[0].b = 0; } //Yellow	
            if (c == 1) { vtx[0].r = 160/255; vtx[0].g = 160 / 255; vtx[0].b = 0; } //Yellow darker	
            if (c == 2) { vtx[0].r = 0; vtx[0].g = 255 / 255; vtx[0].b = 0; } //Green	
            if (c == 3) { vtx[0].r = 0; vtx[0].g = 160 / 255; vtx[0].b = 0; } //Green darker	
            if (c == 4) { vtx[0].r = 0; vtx[0].g = 255 / 255; vtx[0].b = 255 / 255; } //Cyan	
            if (c == 5) { vtx[0].r = 0; vtx[0].g = 160 / 255; vtx[0].b = 160 / 255; } //Cyan darker
            if (c == 6) { vtx[0].r = 160/255; vtx[0].g = 100 / 255; vtx[0].b = 0; } //brown	
            if (c == 7) { vtx[0].r = 110/255; vtx[0].g = 50 / 255; vtx[0].b = 0; } //brown darker

            vtx[0].a = 1.0;
            _engine->drawPixel(vtx);
            c += 1; if (c > 8) { c = 0; }
        }
    }
    //_engine->drawPixel(vtx);

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