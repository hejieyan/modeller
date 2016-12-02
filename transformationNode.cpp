#include <stdio.h>
#include <iostream>
#include "transformationNode.h"

TransformationNode::TransformationNode(){
	int newID = getCurrentID();
	Point3D *temp = new Point3D(0,0,0);
	sendPos = *temp;

	sendTranslate = new TransformationNode(translate, temp);
	sendOrientation = new TransformationNode(rotate, temp);
	sendRotation = new TransformationNode(rotate, temp);
	temp->x = 1;
	temp->y = 1;
	temp->z = 1;
	sendScale = new TransformationNode(scale, temp);

	sceneObject0 = new SceneObject(newID, sendPos, sendTranslate,
							sendOrientation,
							sendRotation,
							sendScale, 
							model);
 	sceneGraph->append(newID, sceneObject0);
}
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