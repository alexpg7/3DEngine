#include "3DEngine.hpp"

Triangle::Triangle(): _p1(), _p2(), _p3(), _norm1(), _norm2(), _norm3()
{

}

Triangle::Triangle(const Triangle& copy)
{
	*this = copy;
}

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 norm1, Vector3 norm2, Vector3 norm3):
_p1(p1), _p2(p2), _p3(p3),
_norm1(norm1), _norm2(norm2), _norm3(norm3)
{

}

Triangle::~Triangle()
{

}

Triangle&	Triangle::operator=(const Triangle& tri)
{
	if (this != &tri)
	{
		_p1 = tri._p1;
		_p2 = tri._p2;
		_p3 = tri._p3;
		_norm1 = tri._norm1;
		_norm2 = tri._norm2;
		_norm3 = tri._norm3;
	}
	return (*this);
}

Vector3&	Triangle::getP1()
{
	return _p1;
}

Vector3&	Triangle::getP2()
{
	return _p2;
}

Vector3&	Triangle::getP3()
{
	return _p3;
}

Vector3&	Triangle::getNormal1()
{
	return _norm1;
}

Vector3&	Triangle::getNormal2()
{
	return _norm2;
}

Vector3&	Triangle::getNormal3()
{
	return _norm3;
}