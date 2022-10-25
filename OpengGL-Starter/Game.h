#pragma once

#include "lib.h"
#include "Engine3D.h"
#include "Shader.h"

#define res					1								//0=160x120 1=360x240 4=640x480
#define ScreenWidth         (1024 / 4) * res						//screen width
#define ScreenHeight        (768  / 4) * res						//screen height
#define ScreenWidth2        (ScreenWidth / 2)               //half of screen width
#define ScreenHeight2       (ScreenHeight / 2)              //half of screen height
#define pixelScale			4/res							//OpenGL pixel scale
#define WindowWidth			(ScreenWidth * pixelScale)		//OpenGL window width
#define WindowHeight		(ScreenHeight * pixelScale)		//OpenGL window height

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
	GLFWwindow	*_window;
	string _windowTitle;

	//Import class
	unique_ptr<Engine3D> _engine;
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

