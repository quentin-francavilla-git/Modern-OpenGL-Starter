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

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(myVTX), (void*)(7 * sizeof(float))); //uv
    glEnableVertexAttribArray(2);
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

void Engine3D::drawTesting()
{
    int size = 1;

    myVTX* vtx = (myVTX*)malloc(sizeof(myVTX) * size);

    if (!vtx)
        return;

    float x = 0;
    float y = 0;
    float c = 0;

    for (y = 0; y < ScreenHeight2; y++)
    {
        for (x = 0; x < ScreenWidth2; x++)
        {
            // Coords
            vtx[0].x = x * (pixelScale / 2);
            vtx[0].y = y * (pixelScale / 2);
            vtx[0].z = 0.0;

            vtx[0].x /= ScreenWidth;
            vtx[0].y /= ScreenHeight;


            // Colors
            if (c == 0) { vtx[0].r = 255 / 255; vtx[0].g = 255 / 255; vtx[0].b = 0; } //Yellow	
            if (c == 1) { vtx[0].r = 160 / 255; vtx[0].g = 160 / 255; vtx[0].b = 0; } //Yellow darker	
            if (c == 2) { vtx[0].r = 0; vtx[0].g = 255 / 255; vtx[0].b = 0; } //Green	
            if (c == 3) { vtx[0].r = 0; vtx[0].g = 160 / 255; vtx[0].b = 0; } //Green darker	
            if (c == 4) { vtx[0].r = 0; vtx[0].g = 255 / 255; vtx[0].b = 255 / 255; } //Cyan	
            if (c == 5) { vtx[0].r = 0; vtx[0].g = 160 / 255; vtx[0].b = 160 / 255; } //Cyan darker
            if (c == 6) { vtx[0].r = 160 / 255; vtx[0].g = 100 / 255; vtx[0].b = 0; } //brown	
            if (c == 7) { vtx[0].r = 110 / 255; vtx[0].g = 50 / 255; vtx[0].b = 0; } //brown darker
            c += 1; if (c > 8) { c = 0; }
            vtx[0].a = 1.0;

            drawPixel(vtx);
        }
    }

    //------
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(myVTX), vtx, GL_DYNAMIC_DRAW);
    ResourceManager::GetShader("shader").Use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);

    free(vtx);
}