#include "boundingBox.h"


BoundingBox::BoundingBox(float size){
	this->far = new Point3D (-size, -size, -size);
	this->near = new Point3D (size, size, size);

}

void BoundingBox::translateBox(Point3D *translateFactor){
	near->x += translateFactor->x;
	near->y += translateFactor->y;
	near->z += translateFactor->z;

	far->x += translateFactor->x;
	far->y += translateFactor->y;
	far->z += translateFactor->z;
}

void BoundingBox::scaleBox(Point3D *scalefactor){
	near->x *= scalefactor->x;
	near->y *= scalefactor->y;
	near->z *= scalefactor->z;

	far->x *= scalefactor->x;
	far->y *= scalefactor->y;
	far->z *= scalefactor->z;
}