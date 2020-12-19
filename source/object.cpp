<<<<<<< Updated upstream
/*****************************************************************************
** File: object.cpp
** Project: 3D Collaborative Game
** Author: Andrew Johnson
** Date Created: 1 August 2020
** Description: Holds all the functions for the Object class
*****************************************************************************/

=======
>>>>>>> Stashed changes

#include "object.h"

/******************************************************************************
 * This is the default constructor
******************************************************************************/
Object::Object () {
<<<<<<< Updated upstream
	vertexShaderSource = load_file("assets/triangle/vertex_shader.vert");
	fragmentShaderSource = load_file("assets/triangle/fragment_shader.frag");
	vertices = new float[9];
	vertices[0] = 20.0f;
	vertices[1] = -0.5f;
	vertices[2] = 20.0f;
	vertices[3] = 20.0f;
	vertices[4] = -0.5f;
	vertices[5] = -20.0f;
	vertices[6] = -20.0f;
	vertices[7] = -0.5f;
	vertices[8] = -20.0f;
}

Object::Object (const char *filepath) {
	char path[200];
	strcpy(path, filepath);
	vertexShaderSource = load_file(strcat(path, "vertex_shader.vert"));
	strcpy(path, filepath);
	fragmentShaderSource = load_file(strcat(path, "fragment_shader2.frag"));
	vertices = new float[9];
	vertices[0] = 20.0f;
	vertices[1] = -0.5f;
	vertices[2] = 20.0f;
	vertices[3] = -20.0f;
	vertices[4] = -0.5f;
	vertices[5] = 20.0f;
	vertices[6] = -20.0f;
	vertices[7] = -0.5f;
	vertices[8] = -20.0f;
=======
	mat = nullptr;
	mesh = nullptr;
	name = "Undefined";
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(0.0f, 0.0f, 0.0f);
}

/******************************************************************************
 * This function loads the object specified by the given object file.
 * Params:
 *		filepath - Filepath from the executable to the object file
******************************************************************************/
void Object::load (const char *filepath) {
	std::string path;
	std::stringstream stream = file_tosstream(filepath);// Store file as stream
	stream >> path;
	if(path.compare("#") != 0) {	// Load material if one is provided
		mat = new Material;
		mat->load(path.c_str());
	}
	stream >> path;
	if(path.compare("#") != 0) {	// Load material if one is provided
		mesh = new Mesh;
		mesh->load(path.c_str());
	}
	compile();
>>>>>>> Stashed changes
}

/******************************************************************************
 * This function prepares the object to be rendered with OpenGL. This should be
 * called every time either the material or the mesh changes.
******************************************************************************/
void Object::compile () {
	GLint posAttrib = glGetAttribLocation(mat->ID, "aPos");
	GLint texAttrib = glGetAttribLocation(mat->ID, "aTexCoord");
	//glEnableClientState(GL_VERTEX_ARRAY);
	mesh->compile(posAttrib, texAttrib);
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	mat->use();
	mat->setInt("texture1", 0);
	mat->setInt("texture2", 1);
}

<<<<<<< Updated upstream
int Object::initialize () {
	// build and compile our shader program
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


	offsetLocation = glGetUniformLocation(shaderProgram, "offset");
    perspectiveMatrixUnif = glGetUniformLocation(shaderProgram, "perspectiveMatrix");

    float fFrustumScale = 1.0f; float fzNear = 0.5f; float fzFar = 100.0f;

	memset(theMatrix, 0, sizeof(float) * 16);

	theMatrix[0] = fFrustumScale;
	theMatrix[5] = fFrustumScale;
	theMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
	theMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
	theMatrix[11] = -1.0f;

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, theMatrix);
	glUseProgram(0);


    // set up vertex data (and buffer(s)) and configure vertex attributes

	glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    
	glDisableClientState(GL_VERTEX_ARRAY);

    return 0;
}

void Object::draw (Camera camera) {
	glUseProgram(shaderProgram);

	float xoffset = 0.5f+camera.location.x;
	float yoffset = 0.0f+camera.location.y;
	float zoffset = 0.0f+camera.location.z;
	float woffset = 0.0f;
	
	glUniform4f(offsetLocation, xoffset*-1, yoffset, zoffset, woffset);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    
/*
    //glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
*/

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
/*

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
*/

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 

	glDisableVertexAttribArray(0);
	glUseProgram(0);
    
    glDisableClientState(GL_VERTEX_ARRAY);

}

void Object::deallocate () {
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
=======
/******************************************************************************
 * This function sets the name to the given name
******************************************************************************/
void Object::set_name (std::string new_name) {
	name = new_name;
}

/******************************************************************************
 * This function returns the current name
******************************************************************************/
std::string Object::get_name () const {
	return name;
}

/******************************************************************************
 * This function sets the position to the given position
******************************************************************************/
void Object::set_position (glm::vec3 new_position) {
	position = new_position;
}

/******************************************************************************
 * This function returns the current position
******************************************************************************/
glm::vec3 Object::get_position () const {
	return position;
}

/******************************************************************************
 * This function translates the position by the given vector
******************************************************************************/
void Object::translate (glm::vec3 movement) {
	position = position + movement;
}

/******************************************************************************
 * This function sets the rotation to the given rotation
******************************************************************************/
void Object::set_rotation (glm::vec3 new_rotation) {
	rotation = new_rotation;
>>>>>>> Stashed changes
}

/******************************************************************************
 * This function returns the current rotation
******************************************************************************/
glm::vec3 Object::get_rotation () const {
	return rotation;
}

/******************************************************************************
 * This function rotates the rotation by the given vector
******************************************************************************/
void Object::rotate (glm::vec3 movement) {
	rotation = rotation + movement;
}

<<<<<<< Updated upstream
void Object::load_image (const char * imagepath) {
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
=======
/******************************************************************************
 * This function sets the scale to the given scale
******************************************************************************/
void Object::set_scale (glm::vec3 new_scale) {
	scale = new_scale;
}
>>>>>>> Stashed changes

/******************************************************************************
 * This function returns the current scale
******************************************************************************/
glm::vec3 Object::get_scale () const {
	return scale;
}

/******************************************************************************
 * This function dilates the scale by the given vector
******************************************************************************/
void Object::dilate (glm::vec3 movement) {
	scale = scale + movement;
}
