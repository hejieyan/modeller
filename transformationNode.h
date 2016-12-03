#include "mathLibrary.h"

enum transType{
	SCALE_OBJECT,
	TRANSLATE_OBJECT,
	ROTATE_OBJECT
};

class TransformationNode{
	private:
		
	public:
		TransformationNode(transType transformation);
		TransformationNode(transType transformation, Point3D *factor);
		void transform(Point3D scale);
};