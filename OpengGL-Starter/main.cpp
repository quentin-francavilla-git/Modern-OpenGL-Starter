#include "Game.h"

// Time
double lastFrame;
int nbFrames;
float deltaTime;

void manageTime();

int main(void)
{
    unique_ptr<Game> game = unique_ptr<Game> (new Game());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(game->getWindow()) && glfwGetKey(game->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        manageTime();

        /* Poll for and process events */
        glfwPollEvents();

        // manage user input
        //game->ProcessInput(dt);
        game->update(deltaTime);
        game->render(deltaTime);
        /* Swap front and back buffers */
        glfwSwapBuffers(game->getWindow());



    }

    glfwTerminate();
    return 0;
}

void manageTime()
{
    double currentFrame = glfwGetTime();
    nbFrames++;

    // If last print was more than 1 sec ago
    deltaTime = currentFrame - lastFrame;
    if (deltaTime >= 1.0) {
        // print and reset timer
        //cout << (1000.0 / double(nbFrames)) << " ms/frame" << endl;
        nbFrames = 0;
        lastFrame += 1.0;
    }
}