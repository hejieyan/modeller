#include "mathLibrary.h"

enum transType{ //the default transformations to be used 
	SCALE_OBJECT,
	TRANSLATE_OBJECT,
	ROTATE_OBJECT
};

class TransformationNode{
	private:
		
	public:
		Point3D *tranValue;
		Point3D *scaleValue;
		Point3D *rotateValue;
		
		TransformationNode(transType transformation);
		TransformationNode(transType transformation, Point3D *factor);
};