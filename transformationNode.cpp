#include <stdio.h>
#include <iostream>
#include "transformationNode.h"

//constructor to save default values in each scene object
TransformationNode::TransformationNode(transType transformation){ 
	switch (transformation){
		case SCALE_OBJECT:
			this->scaleValue = new Point3D(1,1,1);
			break;

		case TRANSLATE_OBJECT:
			this->tranValue = new Point3D(0,0,0);
			break;

		case ROTATE_OBJECT:
			this->rotateValue = new Point3D(0,0,0);
			break;
	}
}

//make transformations 
TransformationNode::TransformationNode(transType transformation, Point3D *factor){
	//transformation = transforms;
	//factor = values;

	switch (transformation){
		case SCALE_OBJECT:
			//printf("%f\n", factor->x);
			glScalef(factor->x, factor->y, factor->z);
			break;

		case TRANSLATE_OBJECT:
			glTranslatef(factor->x, factor->y, factor->z);
			break;

		case ROTATE_OBJECT:
			glRotatef(factor->x, 1, 0, 0);
			glRotatef(factor->y, 0, 1, 0);
			glRotatef(factor->z, 0, 0, 1);
			break;

	}
}