//wrapper class to interact with the pipeline to handle an object
#include "glew.h"
#include "math_3d.h"

class Object {
public:
	Object();
	void changeWireframeView(void);

	void setRotation(Vector3f& rot);
	void setScaling(Vector3f& sca);
	void setTranslation(Vector3f& tra);

	Vector3f& getRotation(void);
	Vector3f& getTranslation(void);
	Vector3f& getScaling(void);

	Matrix4f const *getMatrix(void);
private:
	GLenum currentView;
	
	Vector3f _rotate;
	Vector3f _translation;
	Vector3f _scale;
};

