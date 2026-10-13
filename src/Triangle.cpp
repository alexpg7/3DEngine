#include "3DEngine.hpp"

Triangle::Triangle(): _p1(), _p2(), _p3(), _norm()
{

}

Triangle::Triangle(const Triangle& copy)
{
	*this = copy;
}

Triangle::Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 norm): _p1(p1), _p2(p2), _p3(p3), _norm(norm)
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
		_norm = tri._norm;
	}
	return (*this);
}