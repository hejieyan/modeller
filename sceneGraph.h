#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <list>
#include <vector>
#include "sceneObject.h"
// TODO: Private variables (encapsulation)


using namespace std;

struct node{
	int id;
	//transType tranformType;
	node *next;
};

class SceneGraph {
	private:
		node *root;
		node *currentNode;
		// int listLength;


	public:
		SceneGraph();
		void topMost();
		void append(int ID, SceneObject *addScene);
		//SceneObject findChild(int findID);
		vector<SceneObject> sceneTree;

		
	protected:
		

};

#endif