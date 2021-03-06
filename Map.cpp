#include "Map.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <lodepng.h>

#include <map>

static void SetModel(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T);
static void LoadMesh(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T);
static void LoadTexture(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T);

void LoadMap(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Physics> Phy, RAM& World)
{
	const boost::filesystem::path MapRoot = Path.parent_path();
	boost::property_tree::ptree MapTree;
	boost::property_tree::read_info(Path.string(), MapTree);
	std::map<std::string, std::size_t> Shaders;
	std::string ShaderSource;

	for (boost::property_tree::ptree::value_type& Node : MapTree)
	{
		if (Node.first == "thing")
		{
			std::shared_ptr<Thing> T = World.Rez<Thing>();

			const std::string Shape = Node.second.get("physics.shape", "");

			if (!Shape.empty())
			{
				if (Shape == "square")
				{
					const float size = Node.second.get<float>("physics.shape.size");
					T->PhysicalHandle = Phy->CreateSquare(size, size, size, T->GetID());
				}
			}

			const std::string Gfx = Node.second.get("graphics", "");

			if (!Gfx.empty())
			{
				boost::filesystem::path ShaderPath = MapRoot / Node.second.get<std::string>("graphics.shader");

				std::map<std::string, std::size_t>::iterator Iter = Shaders.find(ShaderPath.string());

				if (Iter == std::end(Shaders))
				{
					ShaderSource.resize(boost::filesystem::file_size(ShaderPath.string()));

					std::ifstream File(ShaderPath.string(), std::ios_base::binary);
					File.read(const_cast<char*>(ShaderSource.data()), ShaderSource.size());
					File.close();

					Shaders[ShaderPath.string()] = Ctx->CreateProgram(ShaderSource);
					Iter = Shaders.insert({ ShaderPath.string(), Ctx->CreateProgram(ShaderSource) }).first;
				}

				T->Shader = Iter->second;

				SetModel(MapRoot / Gfx, Ctx, T);
			}

			if (!Node.second.get_child("pos").empty())
			{

				if (T->PhysicalHandle != std::numeric_limits<std::size_t>::max())//eh...
				{
					Phy->SetPosition(T->PhysicalHandle, {
						Node.second.get<float>("pos.x"),
						Node.second.get<float>("pos.y"),
						Node.second.get<float>("pos.z")
					});
				}
			}
		}
	}
}


void SetModel(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T)
{
	boost::property_tree::ptree Model;
	boost::filesystem::path Dir;

	boost::property_tree::read_info(Path.string(), Model);

	Dir = Path.parent_path();

	for (boost::property_tree::ptree::value_type& Node : Model)
	{
		if (Node.first == "model")
		{
			LoadMesh(Dir / Node.second.get<std::string>("mesh"), Ctx, T);
			LoadTexture(Dir / Node.second.get<std::string>("texture"), Ctx, T);
		}
	}

}

void LoadMesh(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T)
{
	std::vector<Vertex> Vtx;
	std::vector<unsigned int> Indicies;
	Assimp::Importer Importer;

	const aiScene* Scene = Importer.ReadFile(Path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	for (size_t m = 0; m < Scene->mNumMeshes; m++)
	{
		const aiMesh* Mesh = Scene->mMeshes[m];

		Vtx.resize(Mesh->mNumVertices);

		for (size_t v = 0; v < Mesh->mNumVertices; v++)
		{
			Vtx[v].Pos.x = Mesh->mVertices[v].x;
			Vtx[v].Pos.y = Mesh->mVertices[v].y;
			Vtx[v].Pos.z = Mesh->mVertices[v].z;

			Vtx[v].TexCoord.x = Mesh->mTextureCoords[0][v].x;
			Vtx[v].TexCoord.y = Mesh->mTextureCoords[0][v].y;
		}

		assert(Mesh->mNumUVComponents[0] == 2);

		for (size_t f = 0; f < Mesh->mNumFaces; f++)
		{
			const aiFace& Face = Mesh->mFaces[f];

			assert(Face.mNumIndices == 3);

			for (size_t i = 0; i < Face.mNumIndices; i++)
				Indicies.emplace_back(Face.mIndices[i]);
		}
	}

	T->Gfx.mVtx = Ctx->CreateVertexBuffer(Vtx.data(), Vtx.size());
	T->Gfx.mIdx = Ctx->CreateIndexBuffer(Indicies.data(), Indicies.size());
	T->Gfx.mIdxCount = Indicies.size();
}

void LoadTexture(const boost::filesystem::path& Path, std::shared_ptr<Context> Ctx, std::shared_ptr<Thing> T)
{
	std::vector<unsigned char> Bytes;
	unsigned int W, H;

	lodepng::decode(Bytes, W, H, Path.string());

	T->Gfx.mTex = Ctx->CreateTexture(Bytes.data(), Bytes.size(), W, H);
}
