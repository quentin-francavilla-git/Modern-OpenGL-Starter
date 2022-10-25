#include "Engine3D.h"
#include "ResourceManager.h"

Engine3D::Engine3D()
{
    cout << "Engine init." << endl;
    vtxInit();
}

Engine3D::~Engine3D()
{
}

//Private
void Engine3D::vtxInit()
{
    unsigned int VBO;

    // Gen VBuffer & VArray //
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);

    // Bind VBuffer & VArray //
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->EBO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(myVTX), (void*)0); //vec3 pos
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(myVTX), (void*)(3 * sizeof(float))); //vec color
    glEnableVertexAttribArray(1);

    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(myVTX), (void*)(7 * sizeof(float))); //uv
    //glEnableVertexAttribArray(2);
    cout << "VTX init." << endl;
}

void Engine3D::drawPixel(myVTX *vtx)
{
    glBufferData(GL_ARRAY_BUFFER, 1 * sizeof(myVTX), vtx, GL_DYNAMIC_DRAW);
    ResourceManager::GetShader("shader").Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void Engine3D::drawTriangle(myVTX* vtx, int size)
{
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(myVTX), vtx, GL_DYNAMIC_DRAW);
    ResourceManager::GetShader("shader").Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glBindVertexArray(0);
}