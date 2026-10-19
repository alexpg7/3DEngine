#include "3DEngine.hpp"

ObjectsList::ObjectsList(): _path("")
{
}

ObjectsList::ObjectsList(char *path): _path(path)
{
	this->load();
}

ObjectsList::~ObjectsList()
{

}

ObjectsList&	ObjectsList::operator=(const ObjectsList& list)
{
	if (this != &list)
	{
		_path = list._path;
		_objs = list._objs;
	}
	return (*this);
}

Object& ObjectsList::operator[](const int index)
{
	return _objs[index];
}

void ObjectsList::load()
{
	int	n = 0;
	if (!fs::exists(_path) || !fs::is_directory(_path))
	{
		std::cerr << "Error: invalid directory: " << _path << '\n';
		throw std::exception();
		return;
	}

	for (const auto& entry : fs::directory_iterator(_path))
	{
		if (!entry.is_regular_file() || entry.path().extension() != ".obj")
			continue;

		Object obj;
		obj.parse(entry.path().string().data());

		_objs.push_back(obj);
		n++;
	}
	if (n == 0)
	{
		std::cerr << "Warning: no .obj files where found in " << _path << '\n';
		throw std::exception();
	}
}

void	ObjectsList::setPath(char *path)
{
	_path = path;
}

int	ObjectsList::size()
{
	return _objs.size();
}