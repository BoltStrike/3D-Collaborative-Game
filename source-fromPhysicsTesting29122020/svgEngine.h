#ifndef SVGENGINE
#define SVGENGINE

#include "Vector3D.h"
#include "globalPhysics.h"
#include <iostream>
#include "physicsObj.h"
#include "meshCollider.h"
#include <stdio.h>
#include <cstdint>
#include <experimental/filesystem>

#define VIDEO_FILE_NAME "videoOut.mp4"
#define FRAME_RATE 5
#define FRAME_SIZE 1000
#define FRAME_SCALE 10
#define SIDEPANNEL_SIZE 200

static const char* const colors[]={"red","green","blue"};
static const char* TEMP_IMAGE_FILE_NAME="tempImages\temp%d03.svg";
static const char* TEMP_PATH="tempImages\\";
static const char* BLACK="black";
static const char* WHITE="white";

class SvgEngine{
	private:
	PhysicsObj** objs;
	int numObjs;
	int frameNum;
	public:
	SvgEngine(PhysicsObj**,int);
	void genFrame(double);
	void genVideo();
	void writeText(char*,int,int,const char*,FILE*);
	void writeTri(int,int,int,int,int,int,const char* const&,const char*&,FILE*);
};
	

#endif