#include "svgEngine.h"
SvgEngine::SvgEngine(PhysicsObj**objsIn,int numObjsIn){
	this->objs=objsIn;
	this->numObjs=numObjsIn;
	//clear old files
	std::experimental::filesystem::remove_all(TEMP_PATH);
	std::experimental::filesystem::remove(VIDEO_FILE_NAME);
	std::experimental::filesystem::create_directory(TEMP_PATH);	
}
void SvgEngine::genFrame(double time){
	//create the file
	char* temp2;
	sprintf(temp2,TEMP_IMAGE_FILE_NAME,this->frameNum);
	FILE* currentFile=fopen(temp2,"w");
	//fill in the basic frame info
	fprintf(currentFile,"<svg width=\"%d\" height=\"%d\">",FRAME_SIZE+SIDEPANNEL_SIZE,FRAME_SIZE);
	fprintf(currentFile,"<polygon points\"%d,%d %d,%d %d,%d %d,%d\" style=\"fill:black;stroke:black;stroke-width:1\"",FRAME_SIZE,0, FRAME_SIZE+SIDEPANNEL_SIZE,0, FRAME_SIZE+SIDEPANNEL_SIZE,FRAME_SIZE, FRAME_SIZE,FRAME_SIZE);
	sprintf(temp2,"Time: %f4.3 s",time);
	this->writeText(temp2,FRAME_SIZE+(SIDEPANNEL_SIZE/5),FRAME_SIZE/10,WHITE,currentFile);
	sprintf(temp2,"Num: %d",time);
	this->writeText(temp2,FRAME_SIZE+(SIDEPANNEL_SIZE/5),2*FRAME_SIZE/10,WHITE,currentFile);
	sprintf(temp2,"Obj1",this->frameNum);
	this->writeText(temp2,FRAME_SIZE+(SIDEPANNEL_SIZE/5),3*FRAME_SIZE/10,colors[0],currentFile);
	sprintf(temp2,"Obj2",this->frameNum);
	this->writeText(temp2,FRAME_SIZE+(SIDEPANNEL_SIZE/5),4*FRAME_SIZE/10,colors[1],currentFile);
	sprintf(temp2,"Obj3",this->frameNum);
	this->writeText(temp2,FRAME_SIZE+(SIDEPANNEL_SIZE/5),5*FRAME_SIZE/10,colors[2],currentFile);
	//fill in the actual items
	for(int a=0;a<this->numObjs;a++){
		MeshCollider* mesh= (MeshCollider*) this->objs[a]->getCollider();
		for(int b=0, bLimit=mesh->getNumTriangles();b<bLimit;b++){
			this->writeTri((int)(mesh->getTrianglePoint(b,0).x*FRAME_SCALE),(int)(mesh->getTrianglePoint(b,0).y*FRAME_SCALE),
							(int)(mesh->getTrianglePoint(b,1).x*FRAME_SCALE),(int)(mesh->getTrianglePoint(b,1).y*FRAME_SCALE),
							(int)(mesh->getTrianglePoint(b,2).x*FRAME_SCALE),(int)(mesh->getTrianglePoint(b,2).y*FRAME_SCALE),colors[a],BLACK,currentFile);
		}
	}
	fprintf(currentFile,"</svg>");
	//close the file
	fclose(currentFile);
	
}
void SvgEngine::genVideo(){
	char* buffer;
	sprintf(buffer,"ffmpeg -framerate %d -i %s\%03d.png %s",FRAME_RATE,TEMP_IMAGE_FILE_NAME,VIDEO_FILE_NAME);
	system(buffer);
}
void SvgEngine::writeText(char* text,int x,int y,const char* color,FILE* f){
	fprintf(f,"<text x=\"%d\" y=\"%d\">%s<\text>",x,y,text);
}
void SvgEngine::writeTri(int x1,int y1,int x2,int y2,int x3,int y3,const char* const& fill,const char*& line,FILE* f){
	fprintf(f,"<polygon points=\"%d,%d %d,%d %d,%d\" style=\"fill:%s;stroke:%s;stroke-width:1\" />",x1,y1,x2,y2,x3,y3,fill,line);
}