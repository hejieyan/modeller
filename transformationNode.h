#include "mathLibrary.h"

enum transType{
	scale,
	translate,
	rotate
};

class TransformationNode{
	private:
		
	public:
		TransformationNode(transType transformation);
		TransformationNode(transType transformation, Point3D *factor);
};