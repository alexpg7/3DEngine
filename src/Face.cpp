#include "3DEngine.hpp"

Face::Face()
{

}

Face::~Face()
{

}

Face::Face(const Face& copy): _vertex(copy._vertex), _uv(copy._uv),_normal(copy._normal)
{

}

Face& Face::operator=(const Face& obj)
{
	if (this != &obj)
	{
		_vertex = obj._vertex;
		_uv = obj._uv;
		_normal = obj._normal;
	}
	return *this;
}

void Face::addVertex(int vertex, int uv, int normal)
{
	_vertex.push_back(vertex);
	_uv.push_back(uv);
	_normal.push_back(normal);
}

const std::vector<int>& Face::getVertex() const
{
	return _vertex;
}

const std::vector<int>& Face::getNormals() const
{
	return _normal;
}