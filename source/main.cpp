/******************************************************************************
** File: main.cpp
** Project: Collada Export
** Author: Andrew Johnson
** Date Created: 4 July 2020
** Description: Holds the main function of the whole program
******************************************************************************/


//#include "graphics.hpp"


/******************************************************************************
** Function: main
** Description: This is the start of the entire program. 
** Parameters: int argc holds the number of arguments, char **argv holds the 
** string of characters that hold the arguments
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
#include "physicsTestKit.h"
using namespace std;
int main (int argc, char **argv) {
	cout<<"Hello World"<<endl;
	DynamicTestBox box1 = DynamicTestBox(Vector3D(0.0,10.0,0.0),Vector3D(1.0,1.0,1.0));
	StaticTestBox box2 = StaticTestBox(Vector3D(0.0,3.0,0.0),Vector3D(1.0,1.0,1.0));
	PhysicsObj** objs=(PhysicsObj**) malloc(2*sizeof(&box1));
	objs[0]=&box1;
	objs[1]=&box2;
	cout<<"box1:\t"<<box1.getPosition().y;
	cout<<endl;
	for(int i=0;i<20;i++){
		cout<<"Iteration:\t"<<i<<endl;
		box1.update(objs,2,1,0.2);
		cout<<"box1:\t";
		box1.getPosition().display();
		cout<<endl;
		cout<<"box2:\t";
		box2.getPosition().display();
		cout<<endl;
	}
	char* temp;
	cin>>temp;
	free(objs);
	return 0;
}
