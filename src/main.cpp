#include "3DEngine.hpp"

int	main(int narg, char *argv[])
{
	if (narg < 2)
	{
		std::cerr << "No directory specified, please";
		std::cerr << " insert a directory as an argument (containing .obj files)" << std::endl;
	}
	ObjectsList o_list(argv[1]);
	return 0;
}