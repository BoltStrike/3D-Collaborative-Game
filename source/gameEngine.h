#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
#include "../glad/glad.h"
#include "graphics.h"

class GameEngine {
public:
	bool initialize(int, char**);
	void shutdown();

	void run();

	Graphics graphics;

private:
	bool running = false;

	void processInput();
	void update();
	void generateOutputs();
};

#endif 
