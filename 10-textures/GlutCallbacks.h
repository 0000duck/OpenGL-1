#include "Node.h"

class GlutCallbacks
{
public:
	static GlutCallbacks* getInstance();
	static void keySpecial(int key, int x, int y);
	static void key(unsigned char key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void mouseMove(int x, int y);
private:
	GlutCallbacks();
	Node* _root;
	float mouseX;
	float mouseY;

	bool leftPressed;
	bool rightPressed;
	bool middlePressed;
};

