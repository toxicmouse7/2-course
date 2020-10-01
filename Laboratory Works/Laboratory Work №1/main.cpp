#include <ctime>
#include <iostream>

#include "Set.hpp"
#include "IsField.hpp"

int main()
{	
	Set set1("set.txt");
	
	set1.showArr();
	set1.showArrSum();
	set1.showArrMult();

	time_t start = time(NULL);
	if (IsField(set1))
		std::cout << "field" << std::endl;
	time_t end = time(NULL);
	std::cout << "Execution time: " << difftime(end, start) << std::endl;
	
	system("pause");
	return 0;
}