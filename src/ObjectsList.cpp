#include "3DEngine.hpp"

ObjectsList::ObjectsList(): _path(nullptr)
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
		// do
	}
	return (*this);
}

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void ObjectsList::load()
{
	int	n = 0;
	if (!fs::exists(_path) || !fs::is_directory(_path))
	{
		std::cerr << "Error: invalid directory: " << _path << '\n';
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
		std::cerr << "Warning: no .obj files where found in " << _path << '\n';
}

void	ObjectsList::setPath(char *path)
{
	_path = path;
}