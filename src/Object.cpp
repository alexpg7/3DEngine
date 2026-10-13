#include "3DEngine.hpp"

Object::Object()
{
}

Object::Object(const Object& copy)
{
	*this = copy;
}

Object::~Object()
{

}

Object&	Object::operator=(const Object& obj)
{
	if (this != &obj)
	{
		_uv = obj._uv;
		_vertex = obj._vertex;
		_normal = obj._normal;
		_faces = obj._faces;
		_triangles = obj._triangles;
	}
	return (*this);
}

void	Object::parse(char *path)
{
	std::cout << "Parsing " << path << std::endl;
}