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

static int parseIndex(const std::string& index, std::size_t count)
{
	if (index.empty())
		return -1;

	try
	{
		int value = std::stoi(index);

		if (value > 0)
			return value - 1;

		if (value < 0 && static_cast<long long>(count) + value >= 0)
			return static_cast<int>(count) + value;
	}
	catch (...)
	{
		return -1;
	}

	return -1;
}

void Object::parse(char *path)
{
	std::ifstream file(path);

	if (!file.is_open())
		return;

	_vertex.clear();
	_normal.clear();
	_uv.clear();
	_faces.clear();
	_triangles.clear();

	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string type;

		stream >> type;

		if (type.empty() || type[0] == '#')
			continue;

		if (type == "v")
		{
			float x, y, z;

			if (stream >> x >> y >> z)
				_vertex.emplace_back(x, y, z);
		}
		else if (type == "vt")
		{
			float u, v;

			if (stream >> u >> v)
				_uv.emplace_back(u, v);
		}
		else if (type == "vn")
		{
			float x, y, z;

			if (stream >> x >> y >> z)
				_normal.emplace_back(x, y, z);
		}
		else if (type == "f")
		{
			Face face;
			std::string token;

			while (stream >> token)
			{
				if (token[0] == '#')
					break;

				std::string vertexIndex;
				std::string uvIndex;
				std::string normalIndex;

				std::size_t firstSlash = token.find('/');
				std::size_t secondSlash = std::string::npos;

				if (firstSlash == std::string::npos)
				{
					vertexIndex = token;
				}
				else
				{
					vertexIndex = token.substr(0, firstSlash);

					secondSlash = token.find('/', firstSlash + 1);

					if (secondSlash == std::string::npos)
					{
						uvIndex = token.substr(firstSlash + 1);
					}
					else
					{
						uvIndex = token.substr(
							firstSlash + 1,
							secondSlash - firstSlash - 1
						);

						normalIndex = token.substr(secondSlash + 1);
					}
				}

				int vertex = parseIndex(vertexIndex, _vertex.size());
				int uv = parseIndex(uvIndex, _uv.size());
				int normal = parseIndex(normalIndex, _normal.size());

				if (vertex < 0 ||
					static_cast<std::size_t>(vertex) >= _vertex.size())
				{
					face = Face();
					break;
				}

				if (uv >= 0 &&
					static_cast<std::size_t>(uv) >= _uv.size())
					uv = -1;

				if (normal >= 0 &&
					static_cast<std::size_t>(normal) >= _normal.size())
					normal = -1;

				face.addVertex(vertex, uv, normal);
			}

			if (face.getVertex().size() >= 3)
				_faces.push_back(face);
		}
	}

	file.close();
	this->triangulate();
}

void Object::triangulate()
{
	_triangles.clear();

	for (const Face& face : _faces)
	{
		const std::vector<int>& indices = face.getVertex();

		if (indices.size() < 3)
			continue;

		Vector3 p1 = _vertex[indices[0]];

		for (std::size_t i = 1; i + 1 < indices.size(); ++i)
		{
			Vector3 p2 = _vertex[indices[i]];
			Vector3 p3 = _vertex[indices[i + 1]];

			Vector3 edge1 = p2 - p1;
			Vector3 edge2 = p3 - p1;

			Vector3 normal = edge1.cross(edge2);
			normal.normalize();

			_triangles.emplace_back(p1, p2, p3, normal);
		}
	}
}

int	Object::triangleNum()
{
	return _triangles.size();
}

void	Object::clearTriangles2D()
{
	_triangles2D.clear();
}

void	Object::addTriangle2D(Triangle2D tri)
{
	_triangles2D.push_back(tri);
}

Triangle&	Object::getTriangle(int index)
{
	return _triangles[index];
}

Triangle2D&	Object::getTriangle2D(int index)
{
	return _triangles2D[index];
}