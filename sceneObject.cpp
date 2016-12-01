#include "sceneObject.h"

SceneObject::SceneObject(){
	Point3D *temp = new Point3D(0,0,0);
	objPosition = *temp;

	objTranslate = new TransformationNode(translate, temp);
	objOrientation = new TransformationNode(rotate, temp);
	objRotation = new TransformationNode(rotate, temp);
	temp->x = 1;
	temp->y = 1;
	temp->z = 1;
	objScale = new TransformationNode(scale, temp);
	objType = OBJECT_SOLID_CUBE;
}

BoundingBox::BoundingBox(SceneObject* sceneObject) {
	// centerX = sceneObject->objPosition.x;
	// centerY = sceneObject->objPosition.y;
	// centerZ = sceneObject->objPosition.z;

	// calculateMinMax(sceneObject);

	
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

