#include "GraphicsComponent.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

GraphicsComponent::GraphicsComponent(Thing* T) :
	mThing(T)
{
}

void GraphicsComponent::SetModel(const char* Path)
{
	Assimp::Importer Importer;

	const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	for (size_t m = 0; m < Scene->mNumMeshes; m++)
	{
		const aiMesh* Mesh = Scene->mMeshes[m];
		
		assert(Mesh->mNumUVComponents[0] == 2);
		
		for (size_t f = 0; f < Mesh->mNumFaces; f++)
		{
			const aiFace& Face = Mesh->mFaces[f];

			assert(Face.mNumIndices == 3);
			
			for (size_t i = 0; i < Face.mNumIndices; i++)
			{
				const aiVector3D& Vtx = Mesh->mVertices[Face.mIndices[i]];

				mVerticies.push_back(Vtx.x);
				mVerticies.push_back(Vtx.y);
				mVerticies.push_back(Vtx.z);

				const aiVector3D& TexCoord = Mesh->mTextureCoords[0][Face.mIndices[i]];

				mVerticies.push_back(TexCoord.x);
				mVerticies.push_back(TexCoord.y);
			}
		}
	}

	mBuffer = mVerticies.data();
	mNumVerticies = mVerticies.size() / 5;
}
