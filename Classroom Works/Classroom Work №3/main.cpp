#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::experimental::filesystem;

bool comparator(std::pair<fs::path, int> p1, std::pair<fs::path, int> p2)
{
	return p1.second < p2.second;
}

int main(int argc, char* argv[])
{
	fs::path directory = "D:/Gladkov Aleksey MK-201/Aud 3/Directory";
	std::vector<std::pair<fs::path, int>> files;

	for (auto& p : fs::directory_iterator(directory))
	{
		files.push_back(std::make_pair(p, fs::file_size(p)));
	}

	std::sort(files.begin(), files.end(), comparator);

	for (int i = 0, j = 1; i < files.size(); ++i)
	{
		if (files[files.size() - 1 - i].second > 2)
		{
			fs::create_directory(directory.string() + '/' + std::to_string(j));
			fs::copy(files[files.size() - 1 -i].first, directory.string() + '/' + std::to_string(j));
			++j;
		}
	}
	
	system("pause");
	return 0;
}