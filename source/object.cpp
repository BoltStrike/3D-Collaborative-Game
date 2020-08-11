/*****************************************************************************
** File: object.cpp
** Project: 3D Collaborative Game
** Date Created: 1 August 2020
** Description: Holds all the functions for the Object class
*****************************************************************************/


#include "object.h"



Object::Object () {

}

Object::Object (const char *filepath) {
	load(filepath);
}

Object::~Object () {
	delete [] vertices;
	delete [] vertexShaderSource;
	delete [] fragmentShaderSource;
}

void Object::load (const char *filepath) {
	unsigned int length = strlen(filepath);
	char *path = new char[length+100];
	strcpy(path, filepath);
	vertexShaderSource = load_file(strcat(path, "vertex_shader.vert"));
	strcpy(path, filepath);
	fragmentShaderSource = load_file(strcat(path, "fragment_shader.frag"));
	strcpy(path, filepath);


	vertices = verts.get_vertices(strcat(path, "vertices.obj"));
	num_vertices = verts.num_verts;
	verts.print();
	std::cout << verts.num_vertex_indices << std::endl;
	delete [] path;
	initialize();
	std::cout << "initializeation done" << std::endl;
}

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

	glGenBuffers(1, &elementbuffer);
	
    
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
    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, verts.num_vertex_indices*sizeof(verts.vertex_indices[0]), verts.vertex_indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    glEnableClientState(GL_VERTEX_ARRAY);
    
    //glDrawArrays(GL_TRIANGLES, 0, num_vertices*3);
    // glBindVertexArray(0); // no need to unbind it every time 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLES, verts.num_vertex_indices, GL_UNSIGNED_INT, (void*)0);
	
	glDisableVertexAttribArray(0);
	glUseProgram(0);
    
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Object::deallocate () {
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}


char* Object::load_file (const char *filepath) {
	std::ifstream file;
	char *data;
	unsigned long int length;
	
	file.open(filepath, std::ios::in | std::ios::binary);
	if (!file) {
		std::cout << "Failed to open \"" << filepath << "\"" << std::endl;
		return data;
	}
	
	file.seekg(0, std::ios::end);
	length = file.tellg();
	file.seekg(0, std::ios::beg);

	data = new char[length+1];
	data[length] = 0;

	unsigned long int i = 0;
	while (file.good()) {
		data[i] = file.get();
		if (!file.eof()) {
			i++;
		}
	}
	data[i] = 0;
	
	file.close();
	return data;
}


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

	//Everything is in memory now, the file can be closed
	fclose(file);
}

