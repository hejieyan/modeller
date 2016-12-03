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

/*STILL TO DO*/
//Make proper transformation Node
//Implement every transformation
//Ray-Picking

Material material0 = {
	{0.33, 0.22, 0.03, 1.0},	// Ambient
	{0.78, 0.57, 0.11, 1.0},	// Diffuse
	{0.99, 0.91, 0.81, 1.0},	// Specular
	{0, 0, 0, 1},				// Emission
	27.8						// Shininess
};
int ID = 0;
Point3D *sendPos, *sendScale;
TransformationNode *translationNode, *orientationNode, *rotationNode, *scaleNode;

SceneGraph *sceneGraph;

SceneObject *sceneObjectPointer;

int getCurrentID(){
	return ++ID;
}
void insertObject(ObjectType model){
	//nodeScene->AddChild();
	int newID = getCurrentID();
	sceneGraph->topMost();
	
	sendPos = new Point3D(0,0,0);
	sendScale = new Point3D(1,1,1);

	translationNode = new TransformationNode(TRANSLATE_OBJECT);
	orientationNode = new TransformationNode(ROTATE_OBJECT);
	rotationNode = new TransformationNode(ROTATE_OBJECT);
	scaleNode = new TransformationNode(SCALE_OBJECT);

	// objType = OBJECT_SOLID_CUBE;

	sceneObjectPointer = new SceneObject(newID, sendPos, translationNode,
							orientationNode,
							rotationNode,
							sendScale,
							model);
 	sceneGraph->append(newID, sceneObjectPointer);

 	//TODO:Destructor for sceneObjectPointer

}

void updateObj(){
	SceneObject *iterateObjects;
	int i =0;
	for(std::vector<SceneObject>::iterator it = sceneGraph->sceneTree.begin(); it != sceneGraph->sceneTree.end(); ++it) {
		iterateObjects = &sceneGraph->sceneTree[i];
		glPushMatrix();
			glScalef(iterateObjects->objScale->x, iterateObjects->objScale->y, iterateObjects->objScale->z);
			//printf("Item %d: %f, %f, %f\n", i, iterateObjects->objBox->far->x, iterateObjects->objBox->far->y, iterateObjects->objBox->far->z);
			switch(iterateObjects->objType){
				
				case OBJECT_WIRE_CUBE:
					glColor3f(1, 0, 0);
					glutWireCube(1.5);
					glColor3f(0, 1, 0);
					glutWireCube(1);
					break;
				case OBJECT_WIRE_SPHERE:
					glColor3f(1, 0, 0);
					glutWireCube(2);
					glColor3f(0, 1, 0);
					glutWireSphere(1,50,50);
					break;
				}
		glPopMatrix();
		i++;
		}
		

}

void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
		case 'q':
			insertObject(OBJECT_WIRE_CUBE);

			insertObject(OBJECT_WIRE_SPHERE);

			break;

		case 'w':
			Point3D* object1Scale = sceneGraph->sceneTree[2].objScale;
			object1Scale -> x = 3;
			object1Scale -> y = 3;
			object1Scale -> z = 3;

			sceneGraph->sceneTree[2].objBox->scaleBox(object1Scale);

			//TO-DO add transformation Nodes and Bounding box transformations
			break;
	}
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	updateObj();

	
	glutSwapBuffers();
}





// MARK: Callback Functions
void display() {
	// glClearColor(0,0,0,1); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glLoadIdentity();
	glColor3f(1,0,0);



	//SceneObject trial = sceneGraph->findChild(1);
	//sceneTree(1)->objTranslate= 

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
	glutKeyboardFunc(keyboard);

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
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
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