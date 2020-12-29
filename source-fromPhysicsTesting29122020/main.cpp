/******************************************************************************
** File: main.cpp
** Project: 2D Collaborative Game
** Date Created: 4 July 2020
** Description: Holds the main function of the whole program
******************************************************************************/



#include "gameEngine.h"
#include <iostream>

using namespace std;

/******************************************************************************
** Function: main
** Description: This is the start of the entire program. 
** Parameters: int argc holds the number of arguments, char **argv holds the 
** string of characters that hold the arguments
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
#include "physicsTestKit.h"
#include "meshCollider.h"
#include "svgEngine.h"
using namespace std;
int main (int argc, char **argv) {
	//visual collisions
	PhysicsObj** objs=(PhysicsObj**) malloc(sizeof(PhysicsObj*)*2);
	Vector3D* zeroVector=new Vector3D(0,0,0);
	StaticPhysicsObj* staObj=new StaticPhysicsObj(new Vector3D(0,-20,0), zeroVector,(Collider*)new MeshCollider(20));
	DynamicPhysicsObj* dynObj=new DynamicPhysicsObj(new Vector3D(0,10.2,0),new Vector3D(0,10,0), zeroVector,zeroVector,zeroVector,zeroVector,(Collider*)new MeshCollider(10));
	objs[0]=staObj;
	objs[1]=dynObj;
	SvgEngine* svg=new SvgEngine(objs,2);
	double deltaT=0.001;
	double time=0.0;
	svg->genFrame(time);
	for(int i=0;i<50;i++){
		dynObj->update(objs,2,1,deltaT);
		time+=deltaT;
		svg->genFrame(time);
	}
	svg->genVideo();
	//testing the Collider::collideTwoPlanes function
	/*cout<<"running..."<<endl;
	Vector3D nA,pA,nB,pB,resualt;
	for(nA.x=-2;nA.x<=2;nA.x++){
		for(nA.y=-2;nA.y<=2;nA.y++){
			for(nA.z=-2;nA.z<=2;nA.z++){
				for(pA.x=-2;pA.x<=2;pA.x++){
					for(pA.y=-2;pA.y<=2;pA.y++){
						for(pA.z=-2;pA.z<=2;pA.z++){
							for(nB.x=-2;nB.x<=2;nB.x++){
		for(nB.y=-2;nB.y<=2;nB.y++){
			for(nB.z=-2;nB.z<=2;nB.z++){
				for(pB.x=-2;pB.x<=2;pB.x++){
					for(pB.y=-2;pB.y<=2;pB.y++){
						for(pB.z=-2;pB.z<=2;pB.z++){
							//check for parallel planes
							if(!V3DsameNormal(nA,nB)){
								resualt=Collider::collideTwoPlanes(nA,pA,nB,pB);
								//check if poit is on planes
								if(abs(V3Ddot(nA,resualt-pA))>0.0000001 && abs(V3Ddot(nB,resualt-pB))>0.0000001){
									cout<<"Error"<<endl;
									nA.display();
									cout<<endl;
									pA.display();
									cout<<endl;
									nB.display();
									cout<<endl;
									pB.display();
									cout<<endl;
									resualt.display();
									cout<<endl<<endl<<endl<<endl;
									string finalTemp;
									cin>>finalTemp;
								}
							}
						}
					}
				}
			}
		}
	}
						}
					}
				}
			}
			nA.display();
			cout<<endl;
		}
	}
	cout<<"done!"<<endl;
	/*PhysicsObj** pObjs=new PhysicsObj*[2];
	string tmp1="FallingBox";
	DynamicTestObj* fallingBox=new DynamicTestObj(tmp1,new Vector2D(0.0,2,0.0),new SphereCollider(0.75));//BoxCollider(1.0,1.0,1.0));
	string tmp2="StaticBox";
	StaticTestObj* staticBox=new StaticTestObj(tmp2,new Vector2D(0.0,0.0,0.0),new SphereCollider(1.25));//BoxCollider(2.0,2.0,2.0));
	pObjs[0]=fallingBox;
	pObjs[1]=staticBox;
	for(int i=0;i<20;i++){
		cout<<endl<<endl;
		fallingBox->update(pObjs,2,0,0.02);
		fallingBox->dumpInfo();
		staticBox->dumpInfo();
		
	}
	delete fallingBox;
	delete staticBox;*/
	//string finalTemp;
	//cin>>finalTemp;

	return 0;
}
