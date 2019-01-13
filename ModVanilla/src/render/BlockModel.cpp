#include "./BlockModel.hpp"
using namespace CubA4::mod::render;
using namespace CubA4::core::model;

BlockModel::BlockModel()
{
	
}

BlockModel::~BlockModel()
{
	
}

std::vector<Vertex> BlockModel::getVertices() const
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
		//front
		{1,1,1},// up front right 8
		{0,1,1},// up front left 9
		{1,1,0},// down front right 10
		{0,1,0},// down front left 11
		//back
		{1,0,1},// up back right 12
		{0,0,1},// up back left 13
		{1,0,0},// down back right 14
		{0,0,0},// down back left 15
		//right
		{1,1,1},// up front right 16
		{1,0,1},// up back right 17
		{1,1,0},// down front right 18
		{1,0,0},// down back right 19
		//left
		{0,0,1},// up back left 20
		{0,1,1},// up front left 21
		{0,0,0},// down back left 22
		{0,1,0},// down front left 23
	};
}

std::vector<UVWCoords> BlockModel::getUVWCoords() const
{
	return
	{
		//up
		{1,0,0},// up front right 0
		{1,1,0},// up back right 1
		{0,1,0},// up back left 2
		{0,0,0},// up front left 3
		//down
		{1,1,0},// down front right 4
		{1,0,0},// down back right 5
		{0,0,0},// down back left 6
		{0,1,0},// down front left 7
		//front
		{1,1,0},// up front right 8
		{0,1,0},// up front left 9
		{1,0,0},// down front right 10
		{0,0,0},// down front left 11
		//back
		{0,1,0},// up back right 12
		{1,1,0},// up back left 13
		{0,0,0},// down back right 14
		{1,0,0},// down back left 15
		//right
		{0,1,0},// up front right 16
		{1,1,0},// up back right 17
		{0,0,0},// down front right 18
		{1,0,0},// down back right 19
		//left
		{0,1,0},// up back left 20
		{1,1,0},// up front left 21
		{0,0,0},// down back left 22
		{1,0,0},// down front left 23
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