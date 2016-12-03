#include "sceneObject.h"


SceneObject::SceneObject(int ID, Point3D *objPosition, 
							TransformationNode *objTranslate,
							TransformationNode *objOrientation,
							TransformationNode *objRotation,
							Point3D *objScale, 
							ObjectType objType){
	this-> ID = ID;
	this-> objPosition = objPosition;
	this-> objTranslate = objTranslate;
	this-> objOrientation = objOrientation;
	this-> objRotation = objRotation;
	this-> objScale = objScale;
	this-> objType = objType;
	this-> highlight = false;

	switch (this->objType){
		case OBJECT_WIRE_CUBE:
			this->objBox = new BoundingBox(1);
			break;
		case OBJECT_WIRE_SPHERE:
			this->objBox = new BoundingBox(0.5);
			break;
	}	
}



// void BoundingBox::calculateMinMax(SceneObject* sceneObject) {

// 	// FIXME: Probably incorrect; assuming square objects
// 	// Since center is halfway from min and max



// 	// minX = centerX - sceneObject->objectSize / 2;
// 	// maxX = centerX + sceneObject->objectSize / 2;

// 	// minY = centerY - sceneObject->objectSize / 2;
// 	// maxY = centerY + sceneObject->objectSize / 2;

// 	// minZ = centerZ - sceneObject->objectSize / 2;
// 	// maxZ = centerZ + sceneObject->objectSize / 2;

// }


// ObjectType SceneObject::getObjType(){
// 	return this->objType;
// }
void changeMaterial(float x, float y, float z){
	
}
void changeObjType(float x, float y, float z){
	
}

