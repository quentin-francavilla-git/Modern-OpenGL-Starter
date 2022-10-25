#pragma once

#include "lib.h"
#include "Engine3D.h"
#include "Shader.h"

struct SWindowInfo
{
	int res;							//0=160x120 1=360x240 4=640x480
	int screenWidth;					//screen width
	int screenHeight;					//screen height
	int SW2;							//half of screen width
	int SH2;							//half of screen height
	int pixelScale;						//OpenGL pixel scale
	int windowWidth;					//OpenGL window width
	int windowHeight;					//OpenGL window height
	const char* windowTitle;
};

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
private:
	//Data
	GameState State;

	//Window
	SWindowInfo windowInfo;
	GLFWwindow	*_window;
	string _windowTitle;

	//Import class
	unique_ptr<Engine3D> engine;
	Shader shader;

	//Private Functions
	void initWindow();
	void initShader();
	void initOpenGL();

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	void update(float dt);
	void render();

	//Method
	GLFWwindow *getWindow() const;
};

