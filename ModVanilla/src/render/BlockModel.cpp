#include "./BlockModel.hpp"
using namespace CubA4::mod::render;

BlockModel::BlockModel()
{
	
}

BlockModel::~BlockModel()
{
	
}

std::vector<CubA4::core::model::Vertex> BlockModel::getVertices() const
{
	return
	{
		//up
		{1,1,1},		// front right
		{1,0,1},		// back right
		{0,0,1},	// back left
		{0,1,1},		// front left
		//down
		{1,1,0},		// front righ
		{1,0,0},	// back right
		{0,0,0},	// back left
		{0,1,0},	// front left
	};
}

std::vector<unsigned short> BlockModel::getFaceIndices() const
{
	return {
		4, 0, 1, 2, 3, //up
		4, 4, 5, 6, 7, //down
		4, 0, 3, 7, 4, //front
		4, 1, 2, 6, 5, //back
		4, 0, 1, 5, 4, //right
		4, 2, 3, 7, 6 //left
	};
}

std::string BlockModel::getId() const
{
	return "block";
}