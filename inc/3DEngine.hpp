#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>
#include <functional>
#include <algorithm>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>


class Vector3
{
	private:
		float	_x;
		float	_y;
		float	_z;

	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();
		Vector3& operator=(const Vector3& vec);
		Vector3 operator+(const Vector3& vec);
		Vector3 operator-(const Vector3& vec);
		float	norm();
};

class ObjectsList
{
	private:
		std::string	_path;
	public:
		ObjectsList();
		ObjectsList(char *path);
		~ObjectsList();
		ObjectsList& operator=(const ObjectsList& list);
		void load();
		void setPath(char *path);
};