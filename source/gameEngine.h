/******************************************************************************
** File: graphics.hpp
** Project: 3D Collaborative Game
** Date Created: 1 August 2020
** Description: Creates an object to handle all OpenGL and GLUT window 
** operations and commands
******************************************************************************/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#ifndef GLAD_H
#define GLAD_H
#include "../glad/glad.h"
#endif
#include "window_framework.h"

class GameEngine {
private:
	WindowFramework framework;
	int FPS;
	float timeAdd;

	bool running = false;

	void processInput();
	void update();
	void generateOutputs();
	
public:
	GameEngine();
	~GameEngine();
	bool initialize();
	void shutdown();

	void run();
};

#endif 
