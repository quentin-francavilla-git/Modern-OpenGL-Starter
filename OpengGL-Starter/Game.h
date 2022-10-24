#pragma once

#include "lib.h"

//Define
//#define res					1									//0=160x120 1=360x240 4=640x480
//#define screenWidth			160*res								//screen width
//#define screenHeight        120*res								//screen height
//#define SW2					(screenWidth/2)						//half of screen width
//#define SH2					(screenHeight/2)					//half of screen height
//#define pixelScale			4/res								//OpenGL pixel scale
//#define windowWidth			(screenWidth*pixelScale)			//OpenGL window width
//#define windowHeight		(screenHeight*pixelScale)			//OpenGL window height

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
	GLFWwindow	*_window;
	string _windowTitle;

	//Private Functions
	void initWindow(const SWindowInfo &windowInfo);

public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	void update(float dt);
	void render();

	//Method
	GLFWwindow *getWindow() const;
};

