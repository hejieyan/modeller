#include "sceneObject.h"

// SceneObject::SceneObject(){
	

// 	Point3D *temp = new Point3D(0,0,0);
// 	objPosition = *temp;

// 	objTranslate = new TransformationNode(translate, temp);
// 	objOrientation = new TransformationNode(rotate, temp);
// 	objRotation = new TransformationNode(rotate, temp);
// 	temp->x = 1;
// 	temp->y = 1;
// 	temp->z = 1;
// 	objScale = new TransformationNode(scale, temp);
// 	// objType = OBJECT_SOLID_CUBE;
// }

SceneObject::SceneObject(int ID, Point3D objPosition, 
							TransformationNode *objTranslate,
							TransformationNode *objOrientation,
							TransformationNode *objRotation,
							TransformationNode *objScale, 
							ObjectType objType){
	this-> ID = ID;
	this-> objPosition = objPosition;
	this-> objTranslate = objTranslate;
	this-> objOrientation = objOrientation;
	this-> objRotation = objRotation;
	this-> objScale = objScale;
	this-> objType = objType;

	
}


void BoundingBox::calculateMinMax(SceneObject* sceneObject) {

	// FIXME: Probably incorrect; assuming square objects
	// Since center is halfway from min and max



	// minX = centerX - sceneObject->objectSize / 2;
	// maxX = centerX + sceneObject->objectSize / 2;

	// minY = centerY - sceneObject->objectSize / 2;
	// maxY = centerY + sceneObject->objectSize / 2;

	// minZ = centerZ - sceneObject->objectSize / 2;
	// maxZ = centerZ + sceneObject->objectSize / 2;

}


ObjectType SceneObject::getObjType(){
	return this->objType;
}
void changeMaterial(float x, float y, float z){
	
}
void changeObjType(float x, float y, float z){
	
}

