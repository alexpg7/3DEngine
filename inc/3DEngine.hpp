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
#include <filesystem>
#include <array>

namespace fs = std::filesystem;


class Vector3
{
	private:
		float	_x;
		float	_y;
		float	_z;

	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector3& copy);
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
		Vector2(const Vector2& copy);
		~Vector2();
		Vector2& operator=(const Vector2& vec);
		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		float	norm();
};

class Triangle
{
	private:
		Vector3	_p1;
		Vector3	_p2;
		Vector3	_p3;
		Vector3	_norm;
	public:
		Triangle();
		Triangle(const Triangle& copy);
		Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 norm);
		~Triangle();
		Triangle& operator=(const Triangle& tri);
};

class Object
{
	private:
		std::vector<Vector3>	_vertex;
		std::vector<Vector3>	_normal;
		std::vector<Vector2>	_uv;
		std::vector<std::array<int, 3>>	_faces;; //0 -> vertex, 1 -> uv, 2 -> normal
		std::vector<Triangle>	_triangles;
	public:
		Object();
		~Object();
		Object(const Object& copy);
		Object& operator=(const Object& obj);
		void parse(char *path);
};

class ObjectsList
{
	private:
		std::string			_path;
		std::vector<Object>	_objs;
		//lights
	public:
		ObjectsList();
		ObjectsList(char *path);
		~ObjectsList();
		ObjectsList& operator=(const ObjectsList& list);
		void load();
		void setPath(char *path);
};