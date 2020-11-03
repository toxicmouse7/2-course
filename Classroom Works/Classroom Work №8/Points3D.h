#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

struct Point3D
{
	int x;
	int y;
	int z;

	Point3D(int _x, int _y, int _z);
	Point3D();
};

struct Points3D
{
private:
	std::vector<Point3D> points;
public:
	Points3D(std::string filename);
	Point3D find_max_point();
};