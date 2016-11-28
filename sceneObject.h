#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "mathLibrary.h"
#include "sceneGraph.h"

// Private variables (encapsulation)

// Type aliases - can replace Point3D with other two
typedef Point3D Orientation3D, Scale3D;

enum ObjectType {
	// Solid Shapes are 0-8, adding 10 gives the wireframe version
	OBJECT_SOLID_SPHERE = 0,
	OBJECT_SOLID_CUBE,
	OBJECT_SOLID_CONE,
	OBJECT_SOLID_TORUS,
	OBJECT_SOLID_DODECAHEDRON,
	OBJECT_SOLID_OCTAHEDRON,
	OBJECT_SOLID_TETRAHEDRON,
	OBJECT_SOLID_ICOSAHEDRON,
	OBJECT_SOLID_TEAPOT,

	OBJECT_WIRE_SPHERE = 10,
	OBJECT_WIRE_CUBE,
	OBJECT_WIRE_CONE,
	OBJECT_WIRE_TORUS,
	OBJECT_WIRE_DODECAHEDRON,
	OBJECT_WIRE_OCTAHEDRON,
	OBJECT_WIRE_TETRAHEDRON,
	OBJECT_WIRE_ICOSAHEDRON,
	OBJECT_WIRE_TEAPOT;
}

class BoundingBox: public SceneObject {
	private:
		calculateMinMax(Point3D objectCenter);

	protected:
		float minX, maxX,
				minY, maxY,
				minZ, maxZ;

		float centerX, centerY, centerZ;

	public:
		BoundingBox(SceneObject* sceneObject);
		~BoudningBox();
		virtual void update();
}

class SceneObject: public SceneGraphNode {
	protected:
		float objectSize = 1;
		Point3D objectNodePosition;
		Orientation3D objectNodeOrientation;
		Scale3D objectNodeScale;

	public:
		SceneObject();
		~SceneObject();
		virtual void update();
}






#endif