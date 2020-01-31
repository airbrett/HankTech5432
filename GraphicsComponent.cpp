#include "GraphicsComponent.h"

#include "Context.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <lodepng.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

GraphicsComponent::GraphicsComponent(Context* C, Thing* T) :
	mCtx(C),
	mThing(T)
{
}

void GraphicsComponent::SetModel(const boost::filesystem::path& Path)
{
	boost::property_tree::ptree Model;
	boost::filesystem::path Dir;

	boost::property_tree::read_info(Path.string(), Model);

	Dir = Path.parent_path();

	for (boost::property_tree::ptree::value_type& Node : Model)
	{
		if (Node.first == "model")
		{
			LoadMesh(Dir / Node.second.get<std::string>("mesh"));
			LoadTexture(Dir / Node.second.get<std::string>("texture"));
		}
	}
	
}

void GraphicsComponent::LoadMesh(const boost::filesystem::path& Path)
{
	Assimp::Importer Importer;

	mVtx.clear();

	const aiScene* Scene = Importer.ReadFile(Path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

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

void GraphicsComponent::LoadTexture(const boost::filesystem::path& Path)
{
	std::vector<unsigned char> Bytes;
	unsigned int W, H;

	lodepng::decode(Bytes, W, H, Path.string());

	mTex = mCtx->LoadTexture(Bytes.data(), Bytes.size(), W, H);
}
