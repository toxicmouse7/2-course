#include <iostream>

#include "SafeArray.h"
#include "Points3D.h"

template <class T>

void myswap(T& arg1, T& arg2)
{
	auto temp = arg1;

	arg1 = arg2;

	arg2 = temp;
}

int main()
{
	Points3D points("input.txt");
	SafeArray<int> i_vec;
	SafeArray<std::string> s_vec, s_vec1;
	i_vec.push_back(3);
	i_vec.push_back(4);
	s_vec.push_back("string1");
	s_vec1.push_back("string2");

	myswap(s_vec[0], s_vec1[0]);

	Point3D max_point = points.find_max_point();

	std::cout << i_vec[0] << ' ' << i_vec[1] << ' ' << s_vec[0] << ' ' << s_vec1[0] << std::endl;
	std::cout << "Max point: " << max_point.x << ' ' << max_point.y << ' ' << max_point.z << std::endl;

	return 0;
}