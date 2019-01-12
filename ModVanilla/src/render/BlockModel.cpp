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
		{1,1,1},// up front right 0
		{1,0,1},// up back right 1
		{0,0,1},// up back left 2
		{0,1,1},// up front left 3
		//down
		{1,1,0},// down front right 4
		{1,0,0},// down back right 5
		{0,0,0},// down back left 6
		{0,1,0},// down front left 7
		//front 0, 4, 7, 3 | 8, 10, 11, 9
		{1,1,1},// up front right 0 8
		{0,1,1},// up front left 3 9
		{1,1,0},// down front right 4 10
		{0,1,0},// down front left 7 11
		//back 1, 2, 6, 5 | 12, 13, 15, 14
		{1,0,1},// up back right 1 12
		{0,0,1},// up back left 2 13
		{1,0,0},// down back right 5 14
		{0,0,0},// down back left 6 15
		//right 0, 1, 5, 4 | 16, 17, 19, 18
		{1,1,1},// up front right 0 16
		{1,0,1},// up back right 1 17
		{1,1,0},// down front right 4 18
		{1,0,0},// down back right 5 19
		//left 2, 3, 7, 6 | 20, 21, 23, 22
		{0,0,1},// up back left 2 20
		{0,1,1},// up front left 3 21
		{0,0,0},// down back left 6 22
		{0,1,0},// down front left 7 23
	};
}

std::vector<unsigned short> BlockModel::getFaceIndices() const
{
	return {
		4, 0, 3, 2, 1, //up
		4, 4, 5, 6, 7, //down
		4, 8, 10, 11, 9, //front
		4, 12, 13, 15, 14, //back
		4, 16, 17, 19, 18, //right
		4, 20, 21, 23, 22 //left
	};
}

std::string BlockModel::getId() const
{
	return "block";
}