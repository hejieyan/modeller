#include <stdio.h>
#include <stdlib.h>
#include <limits>
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




// Camera Settings
float cameraPosition[] = {5, 2.5, 5};
float cameraUpVector[] = {0, 1, 0};
float cameraTarget[] = {0, 0, 0};
float cameraSpeedFactor = 1.0f;
float cameraRotationX = 0;
float cameraRotationY = 0;

// Lighting settings
bool lightOn = true;
// First light properties
Light light0 = {
	{-1, 0, 0},		// Position
	{0.5, 0, 0, 1},	// Ambient
	{1, 1, 0, 1},	// Diffuse
	{1, 1, 0, 1}	// Specular
};
// Second light properties
Light light1 = {
	{0, 0, -1},		// Position
	{0, 0, 0, 1},	// Ambient
	{0, 1, 1, 1},	// Diffuse
	{0, 1, 1, 1}	// Specular
};


// Materials
Material material0 = {
	{0.33, 0.22, 0.03, 1.0},	// Ambient
	{0.78, 0.57, 0.11, 1.0},	// Diffuse
	{0.99, 0.91, 0.81, 1.0},	// Specular
	{0, 0, 0, 1},				// Emission
	27.8						// Shininess
};

Material material1 = {
	{0.2f, 0.2f, 0.2f, 1.0f},	// Ambient
	{0.8f, 0.8f, 0.8, 1.0f},	// Diffuse
	{0.5f, 0.5f, 0.5f, 1.0f},		// Specular
	{0, 0, 0, 1},				// Emission
	100						// Shininess
};
Material material2 = {
	{0.0215,	0.1745,	0.0215, 1.0},	// Ambient
	{0.07568,	0.61424,	0.07568,1},	// Diffuse
	{0.296648, 	0.296648, 	0.296648,1},		// Specular
	{0, 0, 0, 1},				// Emission
	.25*128						// Shininess
};
Material material3 = {
	{2150.24725, 	0.1995, 	0.0745, 1.0},	// Ambient
	{0.75164, 	0.60648, 	0.22648,1},	// Diffuse
	{0.628281, 	0.555802, 	0.366065,1},		// Specular
	{0, 0, 0, 1},				// Emission
	 0.4*128					// Shininess
};
Material material4 = {
	{0.5,0.5,0.5, 1.0},	// Ambient
	{1, 	0.829, 	0.829,1},	// Diffuse
	{0.633,	0.727811,	0.633,1},		// Specular
	{0, 0, 0, 1},				// Emission
	27.8*128						// Shininess
};

SceneObject *iterateObjects;

int ID = 0;
int closestAddress = -1;
Point3D *sendTransformations = new Point3D (0,0,0);
TransformationNode *translationNode, *orientationNode, *rotationNode, *scaleNode;

//RayPicking elements:
double begin[] = {0,0,0};
double end[] = {0,0,0};

SceneGraph *sceneGraph;

SceneObject *sceneObjectPointer;


// Instructions
void showInstructions() {
	printf("\n\n~~~Simple Modeller!~~~\n"
		"Display all the items you could ever want! \nRay-cast to your heart's desire!\n\n"
		"The program supports the following commands: \n"
		"\t 1-5	- Select Materials\n"
		"\t 6-0	- Insert Objects onto field\n"
		"\t r 	- Reset entire plane (ie delete everything)\n"
		"\t '-' 	- Toggle Lighting on/off\n\n"

		"****Right-Click Objects to delete them.\n"
		"****Left-Click Objects to select them. After selecting:\n"
		"\t x/z         - Scale up/down item\n"
		"\t a/s/d       - Translate (+) across x/y/z axis\n"
		"\t [Alt]+a/s/d - Translate (-) across x/y/z axis\n"
		"\t q/w/e 		- Rotate (+) across x/y/z axis\n"
		"\t [Alt]+q/w/e - Rotate (-) across x/y/z axis\n\n"

		"Camera Commands: \n"
		"\t y/h - Rotate Camera in the x-axis\n"
		"\t g/j - Rotate Camera in the y-axis\n"
		"\t t/u - Rotate Camera in the z-axis\n"
		"\t o/l - Move Viewport Up/Down\n"
		"\t k/; - Move Viewport Left/Right\n"
		"\t i/p - Move Viewport Closer/Farther\n\n"

		"\tESC	- Exit Program\n"
		);
}

// Sets up the initial scene by initializing the camera 
void initCamera() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],  
			cameraTarget[0], cameraTarget[1], cameraTarget[2], 
			0,1,0);

	glRotatef(cameraRotationY,1,0,0);
	glRotatef(cameraRotationX,0,1,0);
	
	sceneGraph = new SceneGraph(); //set up the scene graph for the program
}


void enableLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Sets lighting and material parameters using helper functions
	setLighting(light0, 0);
	//setMaterial(material0);

	setLighting(light1, 1);
	//setMaterial(material1);
}

// Disables Lighting
void disableLighting() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
}

//draw the floor plane
void drawFloor(float ground){
	glColor3f(1,0,1);
	glBegin(GL_QUADS);
		for (int x = -50; x < ground-1; x++) { 
      		for (int z = -50; z < ground-1; z++) {
		    	glNormal3f(0,1,0);
		        glVertex3f(x, 0, z);

		        glNormal3f(0,1,0);
		        glVertex3f(x+1, 0, z);

		        glNormal3f(0,1,0);
		        glVertex3f(x+1, 0, z+1);

		        glNormal3f(0,1,0);
		        glVertex3f(x, 0, z+1);
      }
    }
    glEnd();

}

//returns new id for all 
int getCurrentID(){
	return ++ID;
}

//insert object into scenegraph
void insertObject(ObjectType model){
	//nodeScene->AddChild();
	int newID = getCurrentID();
	sceneGraph->topMost();

	sceneObjectPointer = new SceneObject(newID, model);
 	sceneGraph->append(newID, sceneObjectPointer);
 	//TODO:Destructor for sceneObjectPointer

}


//update sceneobject's values and draw
void updateObj(){
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
	int i =0;
	
	for(std::vector<SceneObject>::iterator it = sceneGraph->sceneTree.begin(); 
		it != sceneGraph->sceneTree.end(); ++it) {

		
		iterateObjects = &sceneGraph->sceneTree[i];
		iterateObjects->pushIt();
				
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//Apply all transformations
		glRotatef(iterateObjects->objRotation->rotateValue->x, 1,0,0);
		glRotatef(iterateObjects->objRotation->rotateValue->y, 0,1,0);
		glRotatef(iterateObjects->objRotation->rotateValue->z, 0,0,1);

		glScalef(iterateObjects->objScale->scaleValue->x,
			iterateObjects->objScale->scaleValue->y, 
			iterateObjects->objScale->scaleValue->z);

		glTranslatef(iterateObjects->objTranslate->tranValue->x,
			iterateObjects->objTranslate->tranValue->y,
			iterateObjects->objTranslate->tranValue->z);

		//Add on Screen
		switch(iterateObjects->objType){
			case OBJECT_SOLID_SPHERE:
				glPushMatrix();
				if(iterateObjects->selected){
					glColor3f(1, 0, 0);
					glutWireCube(2);
				}
				glColor3f(0, 1, 0);
				glutSolidSphere(1, 50,50);
				glPopMatrix();
				break;

			case OBJECT_SOLID_CUBE:
				if(iterateObjects->selected){
					glColor3f(1, 0, 0);
					glutWireCube(1.5);
				}
				glColor3f(0, 1, 0);
				glutSolidCube(1);
				break;

			case OBJECT_SOLID_CONE:
				glPushMatrix();

					if(iterateObjects->selected){
						glTranslatef(0,0,0.5);
						glColor3f(1, 0, 0);
						glutWireCube(1);

				}
				glPopMatrix();
				glColor3f(0, 1, 0);
				glutSolidCone(0.5, 1, 50, 50);
				break;

			case OBJECT_SOLID_TORUS:
				if(iterateObjects->selected){
					glColor3f(1, 0, 0);
					glutWireCube(2);
				}
				glColor3f(0, 1, 0);
				glutSolidTorus(0.5,0.5,50,50);
				break;

			case OBJECT_SOLID_TEAPOT:
				if(iterateObjects->selected){
					glColor3f(1, 0, 0);
					glutWireCube(3);
				}
				glColor3f(0, 1, 0);
				glutSolidTeapot(1);
				break;
			}
		iterateObjects->popIt();
		i++;
		}
	glEnd();
		

}

//Ray-picking
void mouse(int button, int state, int x, int y){
	
	double matrixModelView[16], matrixProjection[16]; 
	int viewport[4]; 

	glGetDoublev(GL_MODELVIEW_MATRIX, matrixModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matrixProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport);

	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	//point on near plane
	gluUnProject(winX, winY, 0.0, matrixModelView, matrixProjection, 
         viewport, &begin[0], &begin[1], &begin[2]); 

	//point on far plane
	gluUnProject(winX, winY, 1.0, matrixModelView, matrixProjection, 
         viewport, &end[0], &end[1], &end[2]);

	//Find magnitude
	end[0] = end[0] - begin[0];
	end[1] = end[1] - begin[1];
	end[2] = end[2] - begin[2];
	double mag = sqrt(end[0]*end[0] + end[1]*end[1] + end[2]*end[2]);

	//unit vector
	end[0] /= mag;
	end[1] /= mag;
	end[2] /= mag;

	//Find intersections
	vector<double> *allIntersections = new vector<double>;
	double intersection;
	int i = 0;
	for(std::vector<SceneObject>::iterator it = sceneGraph->sceneTree.begin(); 
			it != sceneGraph->sceneTree.end(); ++it) {
		iterateObjects = &sceneGraph->sceneTree[i];
		intersection = iterateObjects->objBox->slabIntersect(begin, end);
		allIntersections->insert(allIntersections->begin()+i, intersection);
		i++;
	}

	//Find closest intersection, if any
	double iterateIntersections;
	double closestIntersection = std::numeric_limits<double>::infinity();
	closestAddress = -1;
	for (i = 0; i < allIntersections->size(); ++i){

		iterateIntersections = allIntersections->at(i);

		if (iterateIntersections < closestIntersection && iterateIntersections > 0){
			closestIntersection = iterateIntersections;
			closestAddress = i;
		}
	}

	//Select objects
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		int i=0;
		//deselect everything
		for(std::vector<SceneObject>::iterator it = sceneGraph->sceneTree.begin(); 
				it != sceneGraph->sceneTree.end(); ++it) {
			it->selected = false;
			i++;
		}

		if(closestAddress >-1){
			sceneGraph->sceneTree[closestAddress].selected = true;
		}
	}


	//Right-click to remove
	if(button ==  GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if(closestAddress>-1)
			sceneGraph->sceneTree.erase(sceneGraph->sceneTree.begin() + closestAddress );

	}

	glutPostRedisplay();
}



void keyboard(unsigned char key, int xIn, int yIn)
{

	
	int mod = glutGetModifiers();
	switch (key)
	{
		case 27:	//27 is the esc key
			exit(0);
			break;

		//Materials:
		case '1':
			setMaterial(material1);
			break;
		case '2':
			setMaterial(material0);
			break;
		case '3':
			setMaterial(material2);
			break;
		case '4':
			setMaterial(material3);
			break;
		case '5':
			setMaterial(material4);
			break;



		//Insert Objects 6-0
		case '6':
			insertObject(OBJECT_SOLID_SPHERE);
			break;
		case '7':
			insertObject(OBJECT_SOLID_CUBE);
			break;
		case '8':
			insertObject(OBJECT_SOLID_CONE);
			break;
		case '9':
			insertObject(OBJECT_SOLID_TORUS);
			break;
		case '0':
			insertObject(OBJECT_SOLID_TEAPOT);
			break;


		//reset plane
		case 'r':
			sceneGraph->sceneTree.clear();
			break;

		//Transformations for selected objects:

		//Scale
		case 'x': //scale it up
			if(closestAddress >-1){
				iterateObjects = &sceneGraph->sceneTree[closestAddress];

				if(iterateObjects->selected == true){
					sendTransformations->x = 0.1;
					sendTransformations->y = 0.1;
					sendTransformations->z = 0.1;

					iterateObjects->objScale->scaleValue->x +=sendTransformations->x;
					iterateObjects->objScale->scaleValue->y +=sendTransformations->y;
					iterateObjects->objScale->scaleValue->z +=sendTransformations->z;

					iterateObjects->objBox->scaleBox(sendTransformations);		//Bounding Box
				}
			}
			break;
		case 'z': //scale it down
			if(closestAddress >-1){
				iterateObjects = &sceneGraph->sceneTree[closestAddress];

				if(iterateObjects->selected == true){
					sendTransformations->x = -0.1;
					sendTransformations->y = -0.1;
					sendTransformations->z = -0.1;

					iterateObjects->objScale->scaleValue->x +=sendTransformations->x;
					iterateObjects->objScale->scaleValue->y +=sendTransformations->y;
					iterateObjects->objScale->scaleValue->z +=sendTransformations->z;

					iterateObjects->objBox->scaleBox(sendTransformations);		//Bounding Box
				}
			}
			break;

		//Translate
		case 'a': //Translate across x-axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = -0.1;
						sendTransformations->y = 0;
						sendTransformations->z = 0;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0.1;
						sendTransformations->y = 0;
						sendTransformations->z = 0;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			break;


		case 's': //Translate across y axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = -0.1;
						sendTransformations->z = 0;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 0.1;
						sendTransformations->z = 0;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			break;

		case 'd': //Translate across z axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 0;
						sendTransformations->z = -0.1;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 0;
						sendTransformations->z = 0.1;

						iterateObjects->objTranslate->tranValue->x +=sendTransformations->x;
						iterateObjects->objTranslate->tranValue->y +=sendTransformations->y;
						iterateObjects->objTranslate->tranValue->z +=sendTransformations->z;

						iterateObjects->objBox->translateBox(sendTransformations);		//Bounding Box
					}
				}
			}
			break;

		/**TO DO: Fix rotations, not rotating properly for some reason.
		Maybe pushMatrix() at wrong place?*/

		//Rotate
		case 'q': //Rotate across x-axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = -5;
						sendTransformations->y = 0;
						sendTransformations->z = 0;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 5;
						sendTransformations->y = 0;
						sendTransformations->z = 0;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			break;

		case 'w': //Rotate across y-axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = -5;
						sendTransformations->z = 0;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 5;
						sendTransformations->z = 0;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						//printf("rotating\n");
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			break;

		case 'e': //Rotate across z-axis
			if (mod == GLUT_ACTIVE_ALT){
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 0;
						sendTransformations->z = -5;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			else{
				if(closestAddress >-1){
					iterateObjects = &sceneGraph->sceneTree[closestAddress];

					if(iterateObjects->selected == true){
						sendTransformations->x = 0;
						sendTransformations->y = 0;
						sendTransformations->z = 5;

						iterateObjects->objRotation->rotateValue->x +=sendTransformations->x;
						iterateObjects->objRotation->rotateValue->y +=sendTransformations->y;
						iterateObjects->objRotation->rotateValue->z +=sendTransformations->z;

						//Bounding Box rotation
					}
				}
			}
			break;

		//Lighting Toggle
		case '-':
			if (lightOn){
				lightOn = false;
				disableLighting();
			}
			else{
				lightOn = true;
				enableLighting();
			}
		 	break;

		//camera control
		case 'y':
			cameraPosition[0] += cameraSpeedFactor;
			break;
		case 'g':
			cameraPosition[1] -= cameraSpeedFactor;
			break;
		case 'h':
			cameraPosition[0] -= cameraSpeedFactor;
			break;
		case 'j':
			cameraPosition[1] += cameraSpeedFactor;
			break;
		case 't':
			cameraPosition[2] -= cameraSpeedFactor;
			break;
		case 'u':
			cameraPosition[2] += cameraSpeedFactor;
			break;


		//move camera target
		case 'o':
			cameraTarget[0] += cameraSpeedFactor;
			break;
		case 'k':
			cameraTarget[1] -= cameraSpeedFactor;
			break;
		case 'l':
			cameraTarget[0] -= cameraSpeedFactor;
			break;
		case ';':
			cameraTarget[1] += cameraSpeedFactor;
			break;
		case 'i':
			cameraTarget[2] -= cameraSpeedFactor;
			break;
		case 'p':
			cameraTarget[2] += cameraSpeedFactor;
			break;

	}
	glutPostRedisplay();

}


void display() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	

	glPushMatrix();
	updateObj();
	glPopMatrix();

	drawFloor(50); //TODO draw with different material to make it stand out

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],  
			cameraTarget[0], cameraTarget[1], cameraTarget[2], 
			0,1,0);
	glRotatef(cameraRotationY,1,0,0);
	glRotatef(cameraRotationX,0,1,0);

	
	

	if (lightOn) 
		enableLighting();
	else
		disableLighting();
	
	glutSwapBuffers();
}

void reshape(int width, int height) {
	// Maintain aspect ratio when resizing the window
	glViewport(0, 0, width, height);

	// Models maintain aspect ratio
}

int initCallbacks() {
	initCamera(); // Function to setup camera initial values
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

}


int main(int argc,char** argv) {
	initCamera();
	showInstructions();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modeller");

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	initCallbacks();
	glutMainLoop();
	return 0;

}