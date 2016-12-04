#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "mathLibrary.h"
#include <algorithm>
#include <stdio.h>

#include <limits>

class BoundingBox {
	protected:
		


	public:
		Point3D *far;
		Point3D *near;
		BoundingBox(float size);
		void translateBox(Point3D *translateFactor);
		void scaleBox(Point3D *factor);
		double slabIntersect(double *poi, double *poiD);

};


#endif