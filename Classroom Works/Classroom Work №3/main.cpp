#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#define ALLOWED_SIZE 8

namespace fs = std::filesystem;

bool comparator(std::pair<fs::path, int> p1, std::pair<fs::path, int> p2)
{
	return p1.second < p2.second;
}

size_t find_directory_size(std::string path)
{
	size_t size=0;
    for(fs::recursive_directory_iterator it(path);
        it!=fs::recursive_directory_iterator();
        ++it)
    {   
        if(!fs::is_directory(*it))
            size+=fs::file_size(*it);
    }

	return size;
}

int main(int argc, char* argv[])
{
	fs::path directory = "C:/Users/Алексей/source/repos/2-course/Classroom Works/Classroom Work №3/Files";
	std::vector<std::pair<fs::path, int>> files;

	for (auto& p : fs::directory_iterator(directory))
	{
		files.emplace_back(std::make_pair(p, fs::file_size(p)));
	}

	std::sort(files.begin(), files.end(), comparator);

	/*for (int i = 0, j = 1; i < files.size(); ++i)
	{
		if (files[files.size() - 1 - i].second >= 8)
		{
			fs::create_directory(directory.string() + '/' + std::to_string(j));
			fs::copy(files[files.size() - 1 -i].first, directory.string() + '/' + std::to_string(j));
			++j;
		}
		else if (files[files.size() - 1 - i].second < 8 && files[i].second >= 8)
		{
			fs::create_directory(directory.string() + '/' + std::to_string(j));
			fs::copy(files[i].first, directory.string() + '/' + std::to_string(j));
			++j;
		}
	}*/

	for (int i = 0, j = 1, k = 1; i < files.size(); ++i)
	{
		fs::create_directory(directory.string() + '/' + std::to_string(j));
		while (find_directory_size(directory.string() + '/' + std::to_string(j)) <= ALLOWED_SIZE && i < files.size())
		{
			if (fs::file_size(directory.string() + '/' + std::to_string(j)) + files[i].second <= ALLOWED_SIZE)
			{
				fs::copy(files[i].first, directory.string() + '/' + std::to_string(j));
			}
			else if(files[i].second >= ALLOWED_SIZE)
			{
				std::string bigfile = "BIGFILE_" + std::to_string(k);
				++k;
				fs::create_directory(directory.string() + '/' + bigfile);
				fs::copy(files[i].first, directory.string() + '/' + bigfile);
			}
			else
			{
				break;
			}
			++i;
		}
		++j;
	}
	
	system("pause");
	return 0;
}