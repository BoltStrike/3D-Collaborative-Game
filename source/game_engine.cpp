
#include "game_engine.h"


/******************************************************************************
 * This is the default constructor
******************************************************************************/
GameEngine::GameEngine () {
	//window = new Window;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	fov = 45.0f;
	firstMouse = true;
	yaw = -90.0f;
	pitch = 0.0f;
	
	scene = new Scene;
	
	program_log("Creating physics manager...\n");
	physicsManager=PhysicsManager();
	physicsManager.startUp();
	program_log("Created physics manager\n");
	program_log("Creating player collider...\n");
	playerCollider=new ResolvableCollider(2.0f,0.5f,1.0f,1.0f,20.0f,glm::vec3(0.0f,4.0f,0.0f));
	physicsManager.registerCollider((Collider*)playerCollider);
	program_log("\n");
	program_log("Created player collider\n");
}

/******************************************************************************
 * This is the default destructor
******************************************************************************/
GameEngine::~GameEngine () {
	program_log("Deleting engine...\n");
	
	physicsManager.shutdown();
	delete playerCollider;
	//delete mesh;
	delete mc_cave;
	delete mc_main_grass;
	delete mc_rock;
	delete mc_tree;
	delete mc_trim_grass;
	delete mc_underside;
	delete mc_water;
	
	delete scene;
	//delete window;
	program_log("Deleted engine\n");
}

/******************************************************************************
 * This function initializes a GLFW window with OpenGL.
 *****************************************************************************/
int GameEngine::initialize () {
	program_log("Initializing engine...\n");

	//if(window->create_window(1600, 900, "Reworked Game Engine") != 0)
	//	return -1;

	gwf::initialize_glfw();
	std::string name = "Test Window";
	gwf::create_window(1600, 900, name);
	gwf::set_window(name);
	gwf::set_cursor(false);

	if (!gwf::load_opengl())	return -1;
	gwf::set_depth_test(true);			// Sets depth testing to given Boolean
	gwf::set_backface_culling(true);	// Sets backface culling to given Boolean
	gwf::set_blending(true);			// Sets blending functionality to Boolean
	gwf::set_vsync(true);

	const char *default_scene = "assets/scenes/floating_island.scene";
	scene->load(default_scene);	// Load default scene
	
	//load the colliders:
	//these are staticly listed. waiting on ubJSON for loading from file
	/*
		MeshCollider mc_cave;
		MeshCollider mc_main_grass;
		MeshCollider mc_rock;
		MeshCollider mc_tree;
		MeshCollider mc_trim_grass;
		MeshCollider mc_underside;
		MeshCollider mc_water;*/
	program_log("loading physics mesh colliders...\n");
	/*std::stringstream ss=file_tosstream("assets/objects/physics_testing_ground/meshes_materials/plane.object");
	mesh=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mesh);*/
	std::stringstream ss=file_tosstream("assets/objects/floating_island/meshes_materials/cave.object");
	//program_log("\tCreating cave collider...\n");
	mc_cave= new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	//program_log("\tCreated cave Collider\n");
	//program_log("\tRegistering cave collider...\n");
	physicsManager.registerCollider((Collider*) mc_cave);
	//program_log("\tRegistered cave collider\n");
	//mc_cave->printTriangles();
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/main_grass.object");
	mc_main_grass=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_main_grass);
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/rock.object");
	mc_rock=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_rock);
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/tree.object");
	mc_tree=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_tree);
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/trim_grass.object");
	mc_trim_grass=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_trim_grass);
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/underside.object");
	mc_underside=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_underside);
	ss=file_tosstream("assets/objects/floating_island/meshes_materials/water.object");
	mc_water=new MeshCollider(&ss,100.0f,glm::vec3(),glm::vec3());
	physicsManager.registerCollider((Collider*) mc_water);
	program_log("loaded physics mesh colliders\n");

	program_log("Initalized engine\n\n");
	
	return 0;
}

/******************************************************************************
 * This function is the main game loop. 
******************************************************************************/
void GameEngine::game_loop () {
	program_log("Begin Game Loop\n");
	//mc_cave->printTriangles();
	bool debugLoop=false;
	clock_t currentFrame=clock();
	lastFrame=currentFrame;
	clock_t startTime=currentFrame;
	bool timeOn=false;
	unsigned long long loopNumber=0;
	while (!gwf::should_close()) {
		// Time logic
		if(timeOn){
			currentFrame = clock();
			deltaTime = float(currentFrame - lastFrame)/float(CLOCKS_PER_SEC);
			lastFrame = currentFrame;
		}
		timeOn=true;
		//program_log("delta time: "+std::to_string(deltaTime)+"\n");
		gwf::clear_viewport(0.2f, 0.3f, 0.3f);
		program_log("DeltaT: "+std::to_string(deltaTime)+"\n");

//*********************************/
	
		//glfwGetCursorPos(glfwGetCurrentContext(), &in::cursor_x, &in::cursor_y);

		if (firstMouse) {	// Only for the first time, set the previous location
			lastX = in::cursor_x;
			lastY = in::cursor_y;
			firstMouse = false;
		}

		//std::string message = "X: ";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y: ").append(std::to_string(in::cursor_y)).append("\n"));

		float xoffset = in::cursor_x - lastX;	// x-coordinates go from left to right
		float yoffset = lastY - in::cursor_y; 	// y-coordinates go from bottom to top
		lastX = in::cursor_x;
		lastY = in::cursor_y;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
//*********************************/
	fov -= (float)in::scroll_y;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)

		fov = 45.0f;
//*********************************/
	if (in::btn(in::ESCAPE))	// ESC 
		gwf::close();
	
	if(debugLoop)program_log("\tParsing Keypresses\n");
	float cameraSpeed = 2.5 * deltaTime * 5.0;
	//get the direction in the xz plane
	glm::vec3 movementDir = glm::vec3(0.0f,0.0f,0.0f);
	if (in::btn(in::W))		// W
		movementDir+=cameraFront;
		//cameraPos += cameraSpeed * cameraFront;
	if (in::btn(in::S))		// S
		movementDir-=cameraFront;
		//cameraPos -= cameraSpeed * cameraFront;
	if (in::btn(in::A))		// A
		movementDir-=glm::normalize(glm::cross(cameraFront, cameraUp));
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (in::btn(in::D))		// D
		movementDir+=glm::normalize(glm::cross(cameraFront, cameraUp));
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		
		if(debugLoop)program_log("\tdetermining velocity\n");
		float movementSpeed=10.0f;
		movementDir=glm::normalize(movementDir)*movementSpeed*deltaTime;
		movementDir.y=playerCollider->getVelocity().y;
		if(!isnan(movementDir.x))playerCollider->setVelocity(movementDir);
		if(in::btn(in::SPACE)) playerCollider->setAcceleration(glm::vec3(0.0f,15.0f,0.0f));
		
		//mc_cave->printTriangles();
		
		if(debugLoop)program_log("\tStaring physics update...\n");
		//hook in the physics engine update here
		physicsManager.update(deltaTime);
		cameraPos=playerCollider->getPosition()+glm::vec3(0.0f,1.0f,0.0f);
		if(debugLoop)program_log("\tDone with physics update\n");
		//program_log("\tCamera Position: ",cameraPos,"\n");
		
		program_log("\tPlayer Position: ",playerCollider->getPosition(),"\n");
		
		int width, height;
		gwf::get_dimensions(width, height);
		scene->draw(fov, width, height, cameraPos, cameraFront, cameraUp);		// Draw next frame from this scene
		gwf::swap_buffers();
		//std::string message = "Before: X:";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y:").append(std::to_string(in::cursor_y)).append("\n"));
		in::poll_events();
		//message = "After: X:";
		//program_log(message.append(std::to_string(in::cursor_x)).append(" Y:").append(std::to_string(in::cursor_y)).append("\n"));
		loopNumber++;
	}
	float avrageFPS=float(CLOCKS_PER_SEC)*float(loopNumber)/float(clock() - startTime);
	gwf::terminate_glfw();	// Deallocate GLFW resources
	program_log("Avrage FPS: "+std::to_string(avrageFPS)+"\n"); 
	program_log("Game Loop Stopped\n");
}

