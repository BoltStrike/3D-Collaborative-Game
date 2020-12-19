#include "gameEngine.h"

using namespace std;

GameEngine::GameEngine () {
	//Controls fps cap for game
	FPS = 60;
	timeAdd = (1000 / FPS);
}

GameEngine::~GameEngine () {

}


/*****************************************************************
** Description: Enables all global and default OpenGL settings.
** Parameters: none
** Inputs: none
** Outputs: OpenGL settings enabled
*****************************************************************/
int GameEngine::initialize_window () {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(
			SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(
		window,framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// Window successfully created

	// Enable global OpenGL settings
	glEnable(GL_DEPTH_TEST);
	
	return 0;
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
