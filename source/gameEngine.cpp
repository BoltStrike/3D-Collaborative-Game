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
#include "geometry.h"


using namespace std;

//Controls fps cap for game
int FPS = 60;
float timeAdd = (1000 / FPS);

int shaderProgram;
unsigned int VBO, VAO;
GLFWwindow* window;

bool GameEngine::initialize(int argc, char** argv) {
	const char* vertexShaderSource = graphics.get_vertex_shader();
	const char* fragmentShaderSource = graphics.get_fragment_shader();
	int SCR_WIDTH = graphics.getWidth();
	int SCR_HEIGHT = graphics.getHeight();

	// glfw: initialize and configure
	glfwInit();
	glfwSetErrorCallback(graphics.error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, graphics.framebuffer_size_callback);


	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}


	// build and compile our shader program
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	// link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	//initalization();


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	/*while (!glfwWindowShouldClose(window))
	{
		draw(window, shaderProgram, VAO);
	}*/

	
	
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
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	exit(0);
	return;
}

void GameEngine::processInput() {

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

	if (!glfwWindowShouldClose(window)) {
		graphics.draw(window, shaderProgram, VAO);
	}
	else {
		shutdown();
	}
}

void GameEngine::generateOutputs() {
	//graphics.updateWindow();
}