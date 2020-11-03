#include  "Points3D.h"

Point3D::Point3D(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
{
	
}

Point3D::Point3D() : x(0), y(0), z(0)
{
	
}

Points3D::Points3D(std::string filename)
{
	std::ifstream in_file(filename);

	if (in_file.is_open())
	{
		std::string buffer;

		while(std::getline(in_file, buffer))
		{
			std::istringstream stream(buffer);

			int x, y, z;

			stream >> x >> y >> z;
			
			points.push_back(Point3D(x,y,z));
		}

		in_file.close();
	}
}

Point3D Points3D::find_max_point()
{
	int max_length = 0;
	Point3D null_point(0,0,0);
	Point3D max_point;
	
	for (auto& point : points)
	{
		int length;
		if ((length = sqrt(pow(point.x - null_point.x, 2) + pow(point.y - null_point.y, 2) + pow(point.z - null_point.y, 2)))
			 > max_length)
		{
			max_length = length;
			max_point = point;
		}
	}

	return max_point;
}