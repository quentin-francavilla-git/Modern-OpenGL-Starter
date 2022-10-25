#include "Game.h"

int main(void)
{
    unique_ptr<Game> game = unique_ptr<Game> (new Game());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(game->getWindow()) && glfwGetKey(game->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {


        // manage user input
        // -----------------
        //game->ProcessInput(dt);

        //game->update(dt);

        game->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(game->getWindow());

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}
