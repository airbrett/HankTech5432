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

	mVtx.clear();

	const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	for (size_t m = 0; m < Scene->mNumMeshes; m++)
	{
		const aiMesh* Mesh = Scene->mMeshes[m];

		mVtx.resize(Mesh->mNumVertices);

		for (size_t v = 0; v < Mesh->mNumVertices; v++)
		{
			mVtx[v].Pos.x = Mesh->mVertices[v].x;
			mVtx[v].Pos.y = Mesh->mVertices[v].y;
			mVtx[v].Pos.z = Mesh->mVertices[v].z;

			mVtx[v].TexCoord.x = Mesh->mTextureCoords[0][v].x;
			mVtx[v].TexCoord.y = Mesh->mTextureCoords[0][v].y;
		}
		
		assert(Mesh->mNumUVComponents[0] == 2);
		
		for (size_t f = 0; f < Mesh->mNumFaces; f++)
		{
			const aiFace& Face = Mesh->mFaces[f];

			assert(Face.mNumIndices == 3);
			
			for (size_t i = 0; i < Face.mNumIndices; i++)
				mIndicies.emplace_back(Face.mIndices[i]);
		}
	}
}
