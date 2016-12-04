#include "boundingBox.h"

//default constructor
BoundingBox::BoundingBox(float size){
	this->near = new Point3D (-size, -size, -size);
	this->far = new Point3D (size, size, size);

}

//translate with object transformations
void BoundingBox::translateBox(Point3D *translateFactor){
	near->x += translateFactor->x;
	near->y += translateFactor->y;
	near->z += translateFactor->z;

	far->x += translateFactor->x;
	far->y += translateFactor->y;
	far->z += translateFactor->z;
}

//scale with object scaling
void BoundingBox::scaleBox(Point3D *factor){
	near->x *= (1+factor->x);
	near->y *= (1+factor->y);
	near->z *= (1+factor->z);

	far->x *= (1+factor->x);
	far->y *= (1+factor->y);
	far->z *= (1+factor->z);

}

//Slab intersection, poi =  mouse coordinates, poiD = unit vector
double BoundingBox::slabIntersect(double *poi, double *poiD){

	double nearT = -1 * std::numeric_limits<double>::infinity();
	double farT = std::numeric_limits<double>::infinity();


	/********x-values*********/
	
	if(poiD[0] == 0){	//ray is parallel to planes
		if (poi[0] < near->x || poi[0] > far->x)
			return -1;
	}

	double t1x = (near->x - poi[0]) / poiD[0];
	double t2x = (far->x - poi[0]) / poiD[0];

	if(t1x > t2x) //t1x intersection with near plane
		std::swap(t1x, t2x);

	if(t1x>nearT)
		nearT = t1x;

	if(t2x<farT)
		farT = t2x;

	if(nearT > farT) //box is missed
		return -1;

	if(farT < 0) 	//box behind ray origin
		return -1;

	/********y-values*********/
	
	if(poiD[1] == 0){	//ray is parallel to planes
		if (poi[1] < near->y || poi[1] > far->y)
			return -1;
	}

	double t1y = (near->y - poi[1]) / poiD[1];
	double t2y = (far->y - poi[1]) / poiD[1];

	if(t1y > t2y) //t1x intersection with near plane
		std::swap(t1y, t2y);

	if(t1y>nearT)
		nearT = t1y;

	if(t2y<farT)
		farT = t2y;

	if(nearT > farT) //box is missed
		return -1;

	if(farT < 0) 	//box behind ray origin
		return -1;


	/********z-values*********/
	
	if(poiD[2] == 0){	//ray is parallel to planes
		if (poi[2] < near->z || poi[2] > far->z)
			return -1;
	}

	double t1z = (near->z - poi[2]) / poiD[2];
	double t2z = (far->z - poi[2]) / poiD[2];

	if(t1z > t2z) //t1x intersection with near plane
		std::swap(t1z, t2z);

	if(t2z>nearT)
		nearT = t1z;

	if(t2z<farT)
		farT = t2z;

	if(nearT > farT) //box is missed
		return -1;

	if(farT < 0) 	//box behind ray origin
		return -1;


	return nearT;

}