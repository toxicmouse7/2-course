#include "Set.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

bool Set::check_file(std::ifstream& in_file, std::string& filename)
{
	if (!in_file.is_open())
	{
		std::cout << filename << " wasn't open. Creating empty set." << std::endl;
		in_file.close();
		return false;
	}
	else
	{
		in_file.seekg(0, std::ios::end);
		if (in_file.tellg() == 0)
		{
			std::cout << "File is empty. Creating empty set." << std::endl;
			in_file.close();
			return false;
		}

		in_file.seekg(0, std::ios::beg);
	}

	return true;
}

bool Set::find_power(std::ifstream& in_file)
{
	std::string temp;
	char* endptr = nullptr;
	std::getline(in_file, temp);

	this->power = strtol(temp.c_str(), &endptr, 10);


	if (*endptr != ' ' && *endptr != '\0')
	{
		std::cout << '"' << endptr << "\" acquired while achieving set's power. Closing..." << std::endl;
		in_file.close();
		return false;
	}

	return true;
}

bool Set::fill_array(std::ifstream& in_file)
{
	std::string temp;
	std::getline(in_file, temp);

	std::istringstream is(temp);
	std::string temp_string;

	while (std::getline(is, temp_string, ' '))
	{
		/*if (temp_string.size() > 1)
		{
			std::cout << '"' << temp_string << "\". Only 1 character allowed. Creating empty set." << std::endl;
			in_file.close();
			return false;
		}*/

		this->array[temp_string] = temp_string;
	}

	return true;
}

bool Set::fill_matrix_plus(std::ifstream& in_file)
{
	std::string temp;
	std::getline(in_file, temp);

	std::istringstream is_j(temp);
	std::string j_string;

	for (auto& mp_i : this->array)
	{
		for (auto& mp_j : this->array)
		{
			std::getline(is_j, j_string, ' ');
			this->arraySum[mp_i.second][mp_j.second] = j_string;

			/*if (j_string.size() > 1)
			{
				std::cout << '"' << j_string << "\". Only 1 character allowed. Creating empty set." << std::endl;
				in_file.close();
				return false;
			}*/
		}
	}

	return true;
}

bool Set::fill_matrix_mult(std::ifstream& in_file)
{
	std::string temp;
	std::getline(in_file, temp);

	std::istringstream is_j(temp);
	std::string j_string;

	for (auto& mp_i : this->array)
	{
		for (auto& mp_j : this->array)
		{
			std::getline(is_j, j_string, ' ');
			this->arrayMult[mp_i.second][mp_j.second] = j_string;

			/*if (j_string.size() > 1)
			{
				std::cout << '"' << j_string << "\". Only 1 character allowed. Creating empty set." << std::endl;
				in_file.close();
				return false;
			}*/
		}
	}

	return true;
}

bool Set::IsInArray(const std::string a, const std::string b)
{
	bool flag_a = false, flag_b = false;
	for (auto& mp : this->array)
	{
		if (a == mp.second)
		{
			flag_a = true;
		}

		if (b == mp.second)
		{
			flag_b = true;
		}
	}

	return flag_a && flag_b ? true : false;
}

Set::Set()
{
	this->power = 0;
}

Set::Set(std::string filename)
{
	std::ifstream in_file(filename);

	{
		bool IsFileChecked = this->check_file(in_file, filename);

		if (!IsFileChecked)
		{
			*this = Set();
			return;
		}
	}

	if (!this->find_power(in_file))
	{
		*this = Set();
		return;
	}

	if (!this->fill_array(in_file))
	{
		*this = Set();
		return;
	}

	if (!this->fill_matrix_plus(in_file))
	{
		*this = Set();
		return;
	}

	if (!this->fill_matrix_mult(in_file))
	{
		*this = Set();
		return;
	}
	
	in_file.close();
}

void Set::showArr()
{
	std::cout << "Array: ";
	for (auto& mp : this->array)
	{
		std::cout << mp.second << ' ';
	}
	std::cout << std::endl << std::endl;
}

void Set::showArrSum()
{
	std::cout << "Array sum map: " << std::endl;

	for (auto& mp_2 : arraySum)
	{
		for (auto& mp_1 : mp_2.second)
		{
			std::cout << mp_1.second << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void Set::showArrMult()
{
	std::cout << "Array mult matrix: " << std::endl;

	for (auto& mp_2 : arrayMult)
	{
		for (auto& mp_1 : mp_2.second)
		{
			std::cout << mp_1.second << ' ';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
std::string Set::plus(const std::string& a, const std::string& b)
{	
	return IsInArray(a, b) ? this->arraySum[a][b] : "-1";
}

std::string Set::mult(const std::string& a, const std::string& b)
{
	return IsInArray(a, b) ? this->arrayMult[a][b] : "-1";
}

const std::unordered_map<std::string, std::string> Set::GetArray()
{
	return this->array;
}
