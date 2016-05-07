#include "RawSceneLoader.h"
#include "Scene.h"

void RawSceneLoader::load(Scene& r , const std::string fileName)
{	
	Vector3f positions[] = {
		Vector3f(-0.5f, -0.5f,  0.5f),		    // left front
		Vector3f(-0.5f, -0.5f, -0.5f),		    // left rear
		Vector3f( 0.5f, -0.5f,  0.5f),			// right front
		Vector3f( 0.5f, -0.5f, -0.5f),		    // right rear
		Vector3f( 0.0f,  0.5f,  0.0f),			// peak
	};

	Vector3f colors[] = {
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 0.0f, 1.0f),
		Vector3f(0.0f, 1.0f, 0.0f),
		Vector3f(0.0f, 1.0f, 0.0f),
		Vector3f(1.0f, 0.0f, 0.0f),
	};

	unsigned int indices[] = {
		0, 1, 3,
		0, 3, 2,
		1, 0, 4,
		3, 1, 4,
		2, 3, 4,
		0, 2, 4
	};

	Vector2f tex[] = {
		Vector2f(0.0f, 0.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, 0.0f),
		Vector2f(0.5f, 1.0f),
	};

	r.meshes.push_back(Mesh(5, positions, colors, tex, nullptr, 6, indices));
}