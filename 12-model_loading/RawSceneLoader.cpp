#include "RawSceneLoader.h"
#include "Scene.h"

static void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vector3f* pVertices, unsigned int VertexCount, Vector3f *normals)
{
    for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
        unsigned int Index0 = pIndices[i];
        unsigned int Index1 = pIndices[i + 1];
        unsigned int Index2 = pIndices[i + 2];
		Vector3f v1 = pVertices[Index1] - pVertices[Index0];
		Vector3f v2 = pVertices[Index2] - pVertices[Index0];
        Vector3f Normal = v1.Cross(v2);
        Normal.Normalize();

        normals[Index0] += Normal;
        normals[Index1] += Normal;
        normals[Index2] += Normal;
    }

    for (unsigned int i = 0 ; i < VertexCount ; i++) {
		normals[i].Normalize();
    }
	normals[1] = Vector3f(normals[0].getX(), normals[0].getY(), -normals[0].getZ());
	normals[2] = Vector3f(normals[3].getX(), normals[3].getY(), -normals[3].getZ());
}

bool RawSceneLoader::load(Scene& scene)
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
		Vector3f(1.0f, 1.0f, 0.0f),
		Vector3f(1.0f, 0.0f, 0.0f),
	};
	
	unsigned int indices[] = {
		1, 3, 0,
		0, 3, 2,
		1, 0, 4,
		3, 1, 4,
		2, 3, 4,
		0, 2, 4
	};

	Vector3f normals[sizeof(positions) / sizeof(Vector3f)];
	CalcNormals(indices, sizeof(indices) / sizeof(unsigned int), positions,sizeof(positions) / sizeof(Vector3f), normals);

	Vector2f tex[] = {
		Vector2f(0.0f, 0.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(1.0f, 0.0f),
		Vector2f(0.0f, 0.0f),
		Vector2f(0.5f, 1.0f),
	};

	scene.textures.push_back(Texture());	// load texture from file
	Vector3f lightColorAmbient = Vector3f(0.5f, 0.5f, 0.5f);
	Vector3f lightColorDiffuse = Vector3f(0.0f, 1.0f, 0.0f);
	Vector3f specularColor = Vector3f(1.0f, 0.0f,0.0f);
	//float ambientLightIntensity = 1.0f;
	//float diffuseLightIntensity = 0.5f;
	//float specularIntensity = 1.0f;
	float specularPower = 32.0f;
	Vector3f direction = Vector3f(1.0,0.0f,1.0f);
	/*Material m;
	m._specularColor = specularColor;
	//m._specularIntensity = specularIntensity;
	m._specularPower = specularPower;
	m._light._direction = direction;
	//m._light._intensityAmbient = ambientLightIntensity;
	//m._light._intensityDiffuse = diffuseLightIntensity;
	m._light._lightColorAmbient = lightColorAmbient;
	m._light._lightColorDiffuse = lightColorDiffuse;
	scene.materials.push_back(m);

	scene.meshes.push_back(Mesh());
	for(int i = 0; i < 5; ++i)
		scene.meshes[0].vertices.push_back(Vertex(positions[i], colors[i], tex[i], normals[i]));
	for(int i = 0; i < 18; ++i)
		scene.meshes[0].indices.push_back(indices[i]);
		*/
	return true;
}