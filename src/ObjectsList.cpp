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

void	ObjectsList::load()
{
	std::cout << "Loading " << _path << "..." << std::endl;
}

void	ObjectsList::setPath(char *path)
{
	_path = path;
}