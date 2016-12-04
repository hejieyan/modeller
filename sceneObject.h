#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "mathLibrary.h"
//#include "sceneGraph.h"
#include "transformationNode.h"
#include "boundingBox.h"

// Private variables (encapsulation)

//All object types that are needed
enum ObjectType {
	OBJECT_SOLID_SPHERE,
	OBJECT_SOLID_CUBE,
	OBJECT_SOLID_CONE,
	OBJECT_SOLID_TORUS,
	OBJECT_SOLID_DODECAHEDRON,
	OBJECT_SOLID_OCTAHEDRON,
	OBJECT_SOLID_TETRAHEDRON,
	OBJECT_SOLID_ICOSAHEDRON,
	OBJECT_SOLID_TEAPOT,

	OBJECT_WIRE_SPHERE,
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

	public:
		int ID;
		ObjectType objType;
		BoundingBox *objBox;

		TransformationNode *objTranslate;
		TransformationNode *objRotation;
		TransformationNode *objScale;

		bool selected;

		//constructor
		SceneObject(int ID, ObjectType objType);
		//~SceneObject();

		void changeMaterial(Material changeMat);
		void changeObjType(ObjectType changeObj);

		virtual void pushIt(); //reset to origin for transformations on scene obj
		virtual void popIt();
};

#endif