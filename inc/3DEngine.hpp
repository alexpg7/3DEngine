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
#include <vector>


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

class Vector2
{
	private:
		float	_x;
		float	_y;
		float	_z;

	public:
		Vector2();
		Vector2(float x, float y);
		~Vector2();
		Vector2& operator=(const Vector2& vec);
		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		float	norm();
};

class ObjectsList
{
	private:
		std::string			_path;
		std::vector<Object>	_objs;
	public:
		ObjectsList();
		ObjectsList(char *path);
		~ObjectsList();
		ObjectsList& operator=(const ObjectsList& list);
		void load();
		void setPath(char *path);
};

class Object
{
	private:
		std::vector<Vector3>	_vertex;
		std::vector<Vector3>	_normal;
		std::vector<Vector2>	_uv;
	public:
		Object();
		~Object();
		Object& operator=(const Object& obj);
};