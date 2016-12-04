#include "sceneObject.h"

//update all fields for all new sceneobjects
SceneObject::SceneObject(int ID, ObjectType objType){
	this-> ID = ID;
	this-> objTranslate = new TransformationNode(TRANSLATE_OBJECT);
	this-> objRotation = new TransformationNode(ROTATE_OBJECT);
	this-> objScale = new TransformationNode(SCALE_OBJECT);

	this-> objType = objType;
	this-> selected = false; //defaulted to unselected

	switch (this->objType){ //create bounding boxes for each
		case OBJECT_SOLID_SPHERE:
			this->objBox = new BoundingBox(1);
			break;

		case OBJECT_SOLID_CUBE:
			this->objBox = new BoundingBox(1);
			break;

		case OBJECT_SOLID_CONE:
		{//need brackets to prevent point3d from leaking to other cases
			this->objBox = new BoundingBox(0.5);
			Point3D *temporary = new Point3D(0,0,0.5);
			this->objBox->translateBox(temporary);
			break;
		}

		case OBJECT_SOLID_TORUS:
			this->objBox = new BoundingBox(1);
			break;
		
		case OBJECT_SOLID_TEAPOT:
			this->objBox = new BoundingBox(0.75);
			break;
	}	
}

void SceneObject::pushIt(){ //push so sceneobjects can be transformed properly
	glPushMatrix();
}
void SceneObject::popIt(){
	glPopMatrix();
}

void changeMaterial(float x, float y, float z){
	
}
void changeObjType(float x, float y, float z){
	
}

