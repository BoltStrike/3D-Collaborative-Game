<<<<<<< HEAD
<<<<<<< Updated upstream
=======
/******************************************************************************
** File: graphics.hpp
** Project: 3D Collaborative Game
** Date Created: 1 August 2020
** Description: Creates an object to handle all OpenGL and GLUT window 
** operations and commands
******************************************************************************/

>>>>>>> Stashed changes
=======
>>>>>>> ea22b727cde97addf8bd70078239341323b26e7e
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "../glad/glad.h"
#include "graphics.h"
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
>>>>>>> ea22b727cde97addf8bd70078239341323b26e7e

class GameEngine {
public:
	bool initialize(int, char**);
	void shutdown();

	void run();

	Graphics graphics;

private:
<<<<<<< HEAD
=======
#include "window_framework.h"

class GameEngine {
private:
	WindowFramework framework;
	int FPS;
	float timeAdd;
>>>>>>> Stashed changes
=======
>>>>>>> ea22b727cde97addf8bd70078239341323b26e7e
	bool running = false;

	void processInput();
	void update();
	void generateOutputs();
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
	
public:
	GameEngine();
	~GameEngine();
	bool initialize();
	void shutdown();

	void run();

	Graphics graphics;
>>>>>>> Stashed changes
=======
>>>>>>> ea22b727cde97addf8bd70078239341323b26e7e
};

#endif 
