#include "gameEngine.h"

#include <stdlib.h>
#include <windows.h>

//#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include <cmath>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"


using namespace std;



GameEngine::GameEngine () {
	//Controls fps cap for game
	FPS = 60;
	timeAdd = (1000 / FPS);
}

GameEngine::~GameEngine () {

}

bool GameEngine::initialize() {
	framework.initialize();
	return true;
}

void GameEngine::run() {
	running = true;

	while (running) {
		//cout << "A" << endl;
		processInput();
		//cout << "B" << endl;
		update();
		//cout << "C" << endl;
		generateOutputs();
		//cout << "D" << endl;
	}
}

void GameEngine::shutdown() {
	framework.terminate();
	return;
}

void GameEngine::processInput() {
	framework.key_callback();
}

void GameEngine::update() {
	static uint32_t nextTicks = 0;
	static uint32_t lastTicks = 0;
	//waits for elapsed time to catch up to the frame rate
	while(glfwGetTime()*1000 < nextTicks) {
		//cout << "waiting" << endl;
	}

	uint32_t currentTicks = glfwGetTime()*1000;
	nextTicks = currentTicks + timeAdd;
	//cout << "Time: " << glfwGetTime() << " Next Ticks: " << nextTicks << endl;

	uint32_t deltaTicks = currentTicks - lastTicks;
	float deltat = deltaTicks * 0.001f;

	lastTicks = currentTicks;

	//prevents overflow to negative deltas from ever occuring
	if (deltat < 0.0f) { deltat = 0.0f; }

	//limits to minimum of 20 FPS, meaning delta time wont break during pause in debugging
	//note that it will break when running on systems that can't support 20 FPS or over
	if (deltat > 0.05f) { deltat = 0.05f; }
	//cout << deltat << endl;
	if (!glfwWindowShouldClose(framework.window)) {
		framework.render();
		glfwPollEvents();
	}
	else {
		shutdown();
		exit(0);
	}
}

void GameEngine::generateOutputs() {
	//graphics.updateWindow();
}
