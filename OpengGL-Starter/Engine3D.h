#pragma once

#include "lib.h"

#define res					1								//0=160x120 1=360x240 4=640x480
#define ScreenWidth         (1024 / 4) * res						//screen width
#define ScreenHeight        (768  / 4) * res						//screen height
#define ScreenWidth2        (ScreenWidth / 2)               //half of screen width
#define ScreenHeight2       (ScreenHeight / 2)              //half of screen height
#define pixelScale			4/res							//OpenGL pixel scale
#define WindowWidth			(ScreenWidth * pixelScale)		//OpenGL window width
#define WindowHeight		(ScreenHeight * pixelScale)		//OpenGL window height

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

    void drawTesting();
};

