/*****************************************************************************
** File: graphics.hpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 12 July 2020
** Description: Holds all the functions for the Graphics class
*****************************************************************************/


// the GLFW and OpenGL libraries have to be linked correctly
#include "../glad/glad.h"
#include "../glfw-3.3.2.bin.WIN64/include/GLFW/glfw3.h"

#include <cmath>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "geometry.h"

// The ONLY global object
Graphics graphics;


Graphics::Graphics () {
	window_width = 1280;
	window_height = 720;
	key_sensitivity = 1;
	mouse_sensitivity = 0.1;
}


Graphics::~Graphics () {

}


void Graphics::create (int argc, char **argv) {
	const char *vertexShaderSource = graphics.get_vertex_shader();
	const char *fragmentShaderSource = graphics.get_fragment_shader();
	int SCR_WIDTH = graphics.window_width;
	int SCR_HEIGHT = graphics.window_height;

	// glfw: initialize and configure
    glfwInit();
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
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
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
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

    unsigned int VBO, VAO;
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
    while (!glfwWindowShouldClose(window))
    {
        draw(window, shaderProgram, VAO);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return;
}


void Graphics::draw (GLFWwindow* window, int shaderProgram, unsigned int VAO) {
	// input
    key_callback(window);

    // render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Vector3D offset=graphics.geometry.get_offset();
	double pitch = graphics.geometry.get_pitch();
	double yaw = graphics.geometry.get_yaw();

	perspective_gl(45.0, (double)graphics.window_width / (double)graphics.window_height, 1.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_TEXTURE);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_COLOR);
	// Camera motion
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glTranslatef(offset.x, offset.y, offset.z);
	glTranslatef(0.0, -1.0, -5.0);

	

    // draw our first triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	glTranslatef(offset.x, offset.y, offset.z);
	glTranslatef(0.0, -1.0, -5.0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 

    glFlush();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Graphics::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


const char* Graphics::get_vertex_shader () const {
	return vertexShaderSource;
}

const char* Graphics::get_fragment_shader () const {
	return fragmentShaderSource;
}

void Graphics::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


void Graphics::key_callback(GLFWwindow* window) {
	double sens_key = graphics.get_key_sensitivity();
	Vector3D offset = graphics.geometry.get_offset();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    	graphics.geometry.set_offset(offset.add(Vector3D(0.0,0.0,-sens_key)));
    	std::cout << "w" << std::endl;
    	std::cout << "Offset: " << graphics.geometry.get_offset().x << ", "<< graphics.geometry.get_offset().y << ", " << graphics.geometry.get_offset().z << std::endl; 
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		graphics.geometry.set_offset(offset.add(Vector3D(-sens_key,0.0,0.0)));
		std::cout << "a" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,0.0,sens_key)));
		std::cout << "s" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		graphics.geometry.set_offset(offset.add(Vector3D(sens_key,0.0,0.0)));
		std::cout << "d" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,sens_key,0.0)));
		std::cout << "q" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		graphics.geometry.set_offset(offset.add(Vector3D(0.0,-sens_key,0.0)));
		std::cout << "e" << std::endl;
	}
}


void Graphics::initalization () {
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	perspective_gl(45.0, (double)graphics.window_width / (double)graphics.window_height, 1.0, 200.0);

	// Set the background color
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}


void Graphics::perspective_gl( double fovY, double aspect, double zNear, double zFar )
{
    const double pi = 3.1415926535897932384626433832795;
    double fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}


void Graphics::handleResize (int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective_gl(45.0, (double)width / (double)height, 1.0, 200.0);
	graphics.window_width = width;
	graphics.window_height = height;
	
}


void Graphics::mouse_movement (int x, int y) {
	double sens_mouse = graphics.get_mouse_sensitivity();
	double w = graphics.window_width;
	double h = graphics.window_height;
	graphics.geometry.adjust_view(x, y, w, h, sens_mouse);
	if (x <= w/4 || x >= w*3/4) {
		//glutWarpPointer(w/2, y);
	}
	if (y <= h/4 || y >= h*3/4) {
		//glutWarpPointer(x, h/2);
	}
}

void Graphics::load_image (const char * imagepath) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		printf("Image could not be opened\n"); 
		return;
	}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    	return;
	}
	if ( header[0]!='B' || header[1]!='M' ){
    	printf("Not a correct BMP file\n");
    	return;
	}
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) {
		imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	}
	if (dataPos==0) {
		dataPos=54; // The BMP header is done that way
	}
	
	// Create a buffer
	data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}


double Graphics::get_key_sensitivity () const {
	return key_sensitivity;
}


void Graphics::set_key_sensitivity (double new_key_sensitivity) {
	key_sensitivity = new_key_sensitivity;
}


double Graphics::get_mouse_sensitivity () const {
	return mouse_sensitivity;
}


void Graphics::set_mouse_sensitivity (double new_mouse_sensitivity) {
	mouse_sensitivity = new_mouse_sensitivity;
}

