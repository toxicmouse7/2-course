#include "Set.hpp"
#include <fstream>
#include <iostream>

bool Set::IsInArray(const int a, const int b)
{
	bool flag_a = false, flag_b = false;
	for (int i = 0; i < this->power; ++i)
	{
		if (a == this->array[i])
		{
			flag_a = true;
		}

		if (b == this->array[i])
		{
			flag_b = true;
		}
	}

	return flag_a && flag_b ? true : false;
}

Set::Set()
{
	this->power = 0;
	this->array = nullptr;
	this->arraySum = nullptr;
	this->arrayMult = nullptr;
}

Set::Set(std::string filename)
{
	std::ifstream in_file(filename);

	if (!in_file.is_open())
	{
		std::cout << filename << " wasn't open. Creating empty set." << std::endl;
		*this = Set();
		in_file.close();
		return;
	}

	std::string temp;
	char* endptr = nullptr;
	std::getline(in_file, temp);

	this->power = strtol(temp.c_str(), &endptr, 10);
	

	if (*endptr != ' ' && *endptr != '\0')
	{
		std::cout << "Error was acquired achieving set's power. Creating empty set" << std::endl;
		*this = Set();
		in_file.close();
		return;
	}
	else if(strlen(endptr) > 1)
	{
		std::cout << '"' << endptr << "\" acquired while achieving set's power. Closing..." << std::endl;
		in_file.close();
		exit(2);
	}
	else
	{
		this->array = new int[power];
		std::getline(in_file, temp);

		for (int i = 0; i < this->power; ++i)
		{
			this->array[i] = strtol(temp.c_str(), &endptr, 10);

			if (*endptr != ' ' && *endptr != '\0')
			{
				std::cout << '"' << *endptr << "\" acquired while reading array. Closing..." << std::endl;
				in_file.close();
				exit(1);
			}

			if (i + 1 != this->power)
				temp = endptr;
		}

		if (strlen(endptr) > 1)
		{
			std::cout << "Ignoring \"" << endptr << "\"..." << std::endl;
		}

		std::getline(in_file, temp);
		this->arraySum = new int* [power];
		
		for (int i = 0; i < power; ++i)
		{
			this->arraySum[i] = new int[power];
		}

		for (int i = 0; i < this->power; ++i)
		{
			for (int j = 0; j < this->power; ++j)
			{
				this->arraySum[i][j] = strtol(temp.c_str(), &endptr, 10);
				this->arSum[array[i]][array[j]] = this->arraySum[i][j];
				
				if (*endptr != ' ' && *endptr != '\0')
				{
					std::cout << '"' << *endptr << "\" acquired while reading array. Closing..." << std::endl;
					in_file.close();
					exit(1);
				}

				temp = endptr;
			}
		}

		std::getline(in_file, temp);
		this->arrayMult = new int* [power];

		for (int i = 0; i < power; ++i)
		{
			this->arrayMult[i] = new int[power];
		}

		for (int i = 0; i < this->power; ++i)
		{
			for (int j = 0; j < this->power; ++j)
			{
				this->arrayMult[i][j] = strtol(temp.c_str(), &endptr, 10);

				if (*endptr != ' ' && *endptr != '\0')
				{
					std::cout << '"' << *endptr << "\" acquired while reading array. Closing..." << std::endl;
					in_file.close();
					exit(1);
				}

				temp = endptr;
			}
		}
	}
	
	in_file.close();
}

void Set::showArr()
{
	std::cout << "Array: ";
	for (int i = 0; i < this->power; ++i)
	{
		std::cout << this->array[i] << ' ';
	}
	std::cout << std::endl << std::endl;
}

void Set::showArrSum()
{
	std::cout << "Array sum matrix: " << std::endl;
	
	for (int i = 0; i < this->power; ++i)
	{
		for (int j = 0; j < this->power; ++j)
		{
			std::cout << this->arraySum[i][j] << ' ';
		}
		
		std::cout << std::endl;
	}
	
	std::cout << std::endl;
}

void Set::showArrSum_test()
{
	std::cout << "Array sum map: " << std::endl;

	for (auto& mp_2 : arSum)
	{
		for (auto& mp_1 : mp_2.second)
		{
			std::cout << mp_1.second << ' ';
		}
		std::cout << std::endl;
	}

	
}

void Set::showArrMult()
{
	std::cout << "Array mult matrix: " << std::endl;

	for (int i = 0; i < this->power; ++i)
	{
		for (int j = 0; j < this->power; ++j)
		{
			std::cout << this->arrayMult[i][j] << ' ';
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

int Set::plus(const int a, const int b)
{	
	return IsInArray(a, b) ? this->arraySum[a][b] : -1;
}

int Set::mult(const int a, const int b)
{
	return IsInArray(a, b) ? this->arrayMult[a][b] : -1;
}

const int Set::GetPower()
{
	return this->power;
}
