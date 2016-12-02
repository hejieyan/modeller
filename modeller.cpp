#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "mathLibrary.h"
#include "sceneGraph.h"
#include "sceneObject.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

Material material0 = {
	{0.33, 0.22, 0.03, 1.0},	// Ambient
	{0.78, 0.57, 0.11, 1.0},	// Diffuse
	{0.99, 0.91, 0.81, 1.0},	// Specular
	{0, 0, 0, 1},				// Emission
	27.8						// Shininess
};
int ID = 0;
Point3D sendPos;
TransformationNode *sendTranslate, *sendOrientation, *sendRotation, *sendScale;

SceneGraph *sceneGraph;

SceneObject *sceneObjectPointer;

int getCurrentID(){
	return ++ID;
}
void insertObject(ObjectType model){
	//nodeScene->AddChild();
	int newID = getCurrentID();
	sceneGraph->topMost();
	Point3D *temp = new Point3D(0,0,0);
	sendPos = *temp;

	translationNode = new TransformationNode(translate);
	orientationNode = new TransformationNode(rotate);
	rotationNode = new TransformationNode(rotate);
	scaleNode = new TransformationNode(scale);

	// objType = OBJECT_SOLID_CUBE;

	sceneObjectPointer = new SceneObject(newID, sendPos, translationNode,
							orientationNode,
							rotationNode,
							scaleNode, 
							model);
 	sceneGraph->append(newID, *sceneObjectPointer);

 	//TODO:Destructor for sceneObjectPointer

}
// MARK: Callback Functions
void display() {
	// glClearColor(0,0,0,1); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glLoadIdentity();
	glColor3f(1,0,0);

	insertObject(OBJECT_SOLID_CUBE);
	switch(sceneObjectPointer->objType){
		case OBJECT_SOLID_CUBE:
			glutSolidCube(1);
	}
	insertObject(OBJECT_SOLID_SPHERE);

	switch(sceneObjectPointer->objType){
		case OBJECT_SOLID_CUBE:
			glutSolidCube(1);
	}
	insertObject(OBJECT_WIRE_TEAPOT);
	sceneObjectPointer
	switch(sceneObjectPointer->objType){
		case OBJECT_SOLID_CUBE:
			glutSolidCube(1);
	}
	//glutWireTeapot(0.5);
	//ObjectType getObj = sceneObjectPointer->getObjType();
	

	// switch (getObj){
	// 	case (OBJECT_SOLID_CUBE):
	// 		printf("Solid cube\n");
	// 		insertObject(OBJECT_SOLID_CUBE);
	// 		glutSolidCube(1);
	// 		break;
	//}
	glutSwapBuffers();
}

void reshape(int width, int height) {
	// Maintain aspect ratio when resizing the window
	glViewport(0, 0, width, height);

	// Models maintain aspect ratio
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glOrtho(0, width, 0, height, 0, 10);
	// gluPerspective(180, (float)((width+0.0f)/height), -1, 200);

}

int initCallbacks() {
	sceneGraph = new SceneGraph();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
}

int main(int argc,char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modeller");

	// Clipping
	glEnable(GL_DEPTH_TEST);
	// Setup perspective view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	// gluPerspective(60, 1, 1, 10);
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	
		1.0, 1.0, 1.0,
		0.0,1.0,0.0,
		0.0, 0.0, 0.0
	);

	initCallbacks();
	glutMainLoop();

	return 0;
}