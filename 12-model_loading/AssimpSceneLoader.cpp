#pragma comment(lib, "assimpd.lib")

#include "Configuration.h"
#include "AssimpSceneLoader.h"
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp\IOStream.hpp>
#include <assimp\vector3.h>
#include <assimp\vector2.h>
#include <assimp\material.h>

#include <iostream>

bool AssimpSceneLoader::load(Scene& scene)
{
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(Configuration::getInstance()->getConfiguration("OBJECT"), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if(pScene) {
		processNode(pScene->mRootNode, pScene, scene);
	}
	return true;
}

void AssimpSceneLoader::processNode(aiNode* node, const aiScene* pScene, Scene& sceneDst)
{
	for(unsigned int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = pScene->mMeshes[node->mMeshes[i]];
		initMeshes(mesh, pScene, sceneDst);
	}
	for(unsigned int i = 0; i < node->mNumChildren; ++i) {
		/* recursion */
		processNode(node->mChildren[i],pScene,sceneDst);
	}
}

bool AssimpSceneLoader::initMeshes(aiMesh* pMesh, const aiScene* pScene, Scene& scene)
{
	Mesh m;
	m.materialIndex = pMesh->mMaterialIndex;
	for(unsigned int j = 0; j < pMesh->mNumVertices; ++j) {
		Vector3f pos = Vector3f(0.0f,0.0f,0.0f);
		Vector3f col = Vector3f(0.0f,0.0f,0.0f);
		Vector3f nor = Vector3f(1.0f,1.0f,1.0f);
		Vector2f tex = Vector2f(0.0f,0.0f);
		
		if(pMesh->HasPositions())
			pos = Vector3f(pMesh->mVertices[j].x, pMesh->mVertices[j].y, pMesh->mVertices[j].z);

		if(pMesh->HasVertexColors(0))
			col = Vector3f(pMesh->mColors[0][j].r, pMesh->mColors[0][j].g, pMesh->mColors[0][j].b);

		if(pMesh->HasNormals())
			nor = Vector3f(pMesh->mNormals[j].x, pMesh->mNormals[j].y, pMesh->mNormals[j].z);

		if (pMesh->HasTextureCoords(0)) 
			tex = Vector2f(pMesh->mTextureCoords[0][j].x, pMesh->mTextureCoords[0][j].y);

		m.vertices.push_back(Vertex(pos,col,tex,nor));
	}

	for(unsigned int j = 0; j < pMesh->mNumFaces; ++j) {
		const aiFace face = pMesh->mFaces[j];
		for(unsigned int k = 0; k < face.mNumIndices; ++k) {
			m.indices.push_back(face.mIndices[k]);
		}
	}

//	if(pMesh->mMaterialIndex > 0){
		aiMaterial* material = pScene->mMaterials[pMesh->mMaterialIndex];
		initMaterials(material, pScene, scene);
	//}

	scene.meshes.push_back(m);
	
	return true;
}

bool AssimpSceneLoader::initMaterials(aiMaterial* material, const aiScene* pScene, Scene& scene)
{
	int shading_mode = 0;
	aiColor3D ambientColor;
	aiColor3D diffuseColor;
	aiColor3D specularColor;
	float specularPower;
	float opacity;

	Material m;

	for(unsigned int i = 0; i < material->mNumProperties; ++i) {
		std::cout << material->mProperties[i]->mKey.C_Str() << std::endl;
	}

	if(material->Get(AI_MATKEY_OPACITY,opacity) != AI_SUCCESS) {
		opacity = 1.0f;
	}
	opacity = 0.3;
	if(material->Get(AI_MATKEY_COLOR_AMBIENT,ambientColor) == AI_SUCCESS) {
		/* The ambient color is defined */
		m._light._lightColorAmbient = Vector4f(Vector3f(ambientColor.r, ambientColor.g, ambientColor.b),opacity);
	} else {
		m._light._lightColorAmbient = Vector4f(Vector3f(1.0f,1.0f,1.0f),opacity);
	}
	
	if(material->Get(AI_MATKEY_COLOR_DIFFUSE,diffuseColor) == AI_SUCCESS) {
		/* The diffuse color is defined */
		m._light._lightColorDiffuse = Vector4f(Vector3f(diffuseColor.r, diffuseColor.g, diffuseColor.b), opacity);
	} else {
		m._light._lightColorDiffuse = Vector4f(Vector3f(1.0f,1.0f,1.0f),opacity);
	}

	if(material->Get(AI_MATKEY_COLOR_SPECULAR,specularColor) == AI_SUCCESS) {
		/* The specular color is defined */
		m._specularColor = Vector4f(Vector3f(specularColor.r, specularColor.g, specularColor.b), opacity);
	} else {
		m._specularColor = Vector4f(Vector3f(1.0f,0.0f,0.0f),opacity);
	}
	Vector3f direction = Vector3f(1.0,0.5f,1.0f);
	m._light._direction = direction;

	if(material->Get(AI_MATKEY_SHININESS ,specularPower) != AI_SUCCESS) {
		specularPower = 3200.0f;
	} 
	
	m._specularPower = specularPower;
	scene.materials.push_back(m);

	/*	Now let's count the textures (if there are some) */
	for(unsigned int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); ++j) {
		aiString path;
		if(material->GetTexture(aiTextureType_DIFFUSE,0, &path) == AI_SUCCESS) {
			scene.textures.push_back(Texture());
		}
	}
	
	return true;
}