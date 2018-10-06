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
		{0.5,0.5,0.5},
		{0.5,-0.5,0.5},
		{-0.5,-0.5,0.5},
		{-0.5,0.5,0.5},
		//down
		{0.5,0.5,-0.5},
		{0.5,-0.5,-0.5},
		{-0.5,-0.5,-0.5},
		{-0.5,0.5,-0.5},
	};
}

std::vector<unsigned short> BlockModel::getFaceIndices() const
{
	return {};
}