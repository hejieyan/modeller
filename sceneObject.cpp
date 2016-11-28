#include "sceneObject.h"

BoundingBox::calculateMinMax(SceneObject* sceneObject) {
	// FIXME: Probably incorrect; assuming square objects
	// Since center is halfway from min and max
	minX = centerX - sceneObject->objectSize / 2;
	maxX = centerX + sceneObject->objectSize / 2;

	minY = centerY - sceneObject->objectSize / 2;
	maxY = centerY + sceneObject->objectSize / 2;

	minZ = centerZ - sceneObject->objectSize / 2;
	maxZ = centerZ + sceneObject->objectSize / 2;

}

BoundingBox::BoundingBox(SceneObject* sceneObject) {
	centerX = sceneObject->objectNodePosition.x;
	centerY = sceneObject->objectNodePosition.y;
	centerZ = sceneObject->objectNodePosition.z;

	calculateMinMax(sceneObject);
}