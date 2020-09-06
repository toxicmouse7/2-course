#pragma once
#include <map>
#include <string>

class Set
{
private:
	int power;
	int* array;
	int** arraySum;
	std::map<int, std::map<int, int>> arSum;
	int** arrayMult;

	bool IsInArray(const int, const int);
public:
	Set();
	Set(std::string filename);
	void showArr();
	void showArrSum();
	void showArrSum_test();
	void showArrMult();
	int plus(const int, const int);
	int mult(const int, const int);
	const int GetPower();
};
