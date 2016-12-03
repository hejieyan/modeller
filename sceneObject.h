#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "mathLibrary.h"
//#include "sceneGraph.h"
#include "transformationNode.h"
#include "boundingBox.h"

// Private variables (encapsulation)

// Type aliases - can replace Point3D with other two
// typedef TransformationNode TranslationNode, OrientationNode,RotationNode, ScaleNode;

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
	OBJECT_WIRE_TEAPOT
};




class SceneObject {
	protected:
		//float objectSize = 1;
		
		bool  highlight;
		
		Point3D *objPosition;
		TransformationNode *objTranslate;
		TransformationNode *objOrientation;
		TransformationNode *objRotation;
		
		
		//Material objMaterial;
		//Light objLight;
		//BoundingBox *objBox;



	public:
		int ID;
		Point3D *objScale;
		ObjectType objType;
		BoundingBox *objBox;

		SceneObject(int ID, Point3D *objPosition, 
							TransformationNode *objTranslate,
							TransformationNode *objOrientation,
							TransformationNode *objRotation,
							Point3D *objScale, 
							ObjectType objType);
		//~SceneObject();
		//void updateObj();

		ObjectType getObjType();

		void changeMaterial(Material changeMat);
		void changeObjType(ObjectType changeObj);

};



// class BoundingBox: public SceneObject {
// 	private:
// 		void calculateMinMax(SceneObject* sceneObject);

// 	protected:
// 		float minX, maxX,
// 				minY, maxY,
// 				minZ, maxZ;
// 		Point3D min, max;

// 		float centerX, centerY, centerZ;

// 	public:
// 		//~BoundingBox();
// 		//virtual void update();
// };


#endif