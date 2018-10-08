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
		{0.5,0.5,0.5},		// front right
		{0.5,-0.5,0.5},		// back right
		{-0.5,-0.5,0.5},	// back left
		{-0.5,0.5,0.5},		// front left
		//down
		{0.5,0.5,-0.5},		// front righ
		{0.5,-0.5,-0.5},	// back right
		{-0.5,-0.5,-0.5},	// back left
		{-0.5,0.5,-0.5},	// front left
	};
}

std::vector<unsigned short> BlockModel::getFaceIndices() const
{
	return {
		4, 0, 1, 2, 3, //up
		4, 4, 5, 6, 7, //down
		4, 0, 3, 4, 7, //front
		4, 1, 2, 5, 6, //back
		4, 0, 1, 4, 5, //right
		4, 2, 3, 6, 7 //left
	};
}