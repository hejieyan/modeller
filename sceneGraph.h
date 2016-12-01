#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <list>
// TODO: Private variables (encapsulation)


using namespace std;

class SceneGraphNode {
	public:
		// Constructor
		SceneGraphNode() {
		}
		// Release object from memory
		void release() {
			delete this;
		}
		// Destroy all the children
		void destroy() {
			for (list<SceneGraphNode*>::iterator childNode = childrenList.begin();
					childNode != childrenList.end(); childNode++) {
				(*childNode)->release();
			}
			childrenList.clear();
		}
		// Destructor
		virtual ~SceneGraphNode() {
			destroy();
		}
		
		// Update scene node
		virtual void update() {
			// loop through list and update children
			for (list<SceneGraphNode*>::iterator childNode = childrenList.begin(); 
					childNode != childrenList.end(); childNode++) {
				(*childNode)->update();
			}
		}
		
		// Add child node to the current node
		void AddChild (SceneGraphNode* parentNode) {
			childrenList.push_back(parentNode);
		}

	protected:
		// List of children nodes
		list<SceneGraphNode*> childrenList;
};

#endif