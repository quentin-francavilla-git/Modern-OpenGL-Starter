#pragma once

#include "lib.h"

typedef struct
{
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
    float a;

    //float u;
    //float v;
} myVTX;

class Engine3D
{
private:
    unsigned int _VAO;

	void vtxInit();
public:
	Engine3D();
	virtual ~Engine3D();


    void drawPixel(myVTX* vtx);
    void drawTriangle(myVTX* vtx, int size);
};

