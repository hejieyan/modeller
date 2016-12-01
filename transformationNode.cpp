#include <stdio.h>
#include <iostream>
#include "transformationNode.h"


TransformationNode::TransformationNode(transType transformation, Point3D *factor){
	//transformation = transforms;
	//factor = values;

	switch (transformation){
		case scale:
			glScalef(factor->x, factor->y, factor->z);
			break;

		case translate:
			glTranslatef(factor->x, factor->y, factor->z);
			break;

		case rotate:
			glRotatef(factor->x, 1, 0, 0);
			glRotatef(factor->y, 0, 1, 0);
			glRotatef(factor->z, 0, 0, 1);
			break;

	}
}