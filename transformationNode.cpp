#include <stdio.h>
#include <iostream>
#include "transformationNode.h"

TransformationNode::TransformationNode(transType transformation){
	switch (transformation){
		case SCALE_OBJECT:
			glScalef(1,1,1);
			break;

		case TRANSLATE_OBJECT:
			glTranslatef(0,0,0);
			break;

		case ROTATE_OBJECT:
			glRotatef(0, 1,0,0);
			glRotatef(0, 0,1,0);
			glRotatef(0, 0,0,1);
			break;
	}
}

void TransformationNode::transform(Point3D scale){
	glScalef(scale.x, scale.y, scale.z);
}
TransformationNode::TransformationNode(transType transformation, Point3D *factor){
	//transformation = transforms;
	//factor = values;

	switch (transformation){
		case SCALE_OBJECT:
			printf("%f\n", factor->x);
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