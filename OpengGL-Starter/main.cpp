#include "Game.h"

int main(void)
{
    unique_ptr<Game> game = unique_ptr<Game> (new Game());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(game->getWindow()) && glfwGetKey(game->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {

        /* Poll for and process events */
        glfwPollEvents();

        // manage user input
        game->processInput();
        game->updateDt();
        game->update();
        game->render();
        /* Swap front and back buffers */
        glfwSwapBuffers(game->getWindow());

    }
    glfwTerminate();
    return 0;
}