#include "mathLibrary.h"

enum transType{
	scale,
	translate,
	rotate
};

class TransformationNode{
	public:
		TransformationNode(transType transformation, Point3D *factor);
};