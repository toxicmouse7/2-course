#pragma once
#include <unordered_map>
#include <string>

class Set
{
private:
	int power;
	std::unordered_map<std::string, std::string> array;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> arraySum;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> arrayMult;
	bool check_file(std::ifstream& in_file, std::string& filename);
	bool find_power(std::ifstream& in_file);
	bool fill_array(std::ifstream& in_file);
	bool fill_matrix_plus(std::ifstream& in_file);
	bool fill_matrix_mult(std::ifstream& in_file);
	
	bool IsInArray(const std::string, const std::string);
public:
	Set();
	Set(std::string filename);
	void showArr();
	void showArrSum();
	void showArrMult();
	std::string plus(const std::string&, const std::string&);
	std::string mult(const std::string&, const std::string&);
	const std::unordered_map<std::string, std::string> GetArray();
};
