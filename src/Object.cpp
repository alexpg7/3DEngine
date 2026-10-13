#include "3DEngine.hpp"

Object::Object()
{
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
	}
	return (*this);
}