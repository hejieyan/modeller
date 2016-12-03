#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "mathLibrary.h"

class BoundingBox {
	protected:
		Point3D *far;
		Point3D *near;


	public:
		BoundingBox(float size);
		void translateBox(Point3D *translateFactor);
		void scaleBox(Point3D *scaleFactor);

};


#endif