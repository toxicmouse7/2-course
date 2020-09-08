#include <iostream>

#include "Set.hpp"
#include "IsField.hpp"

int main()
{	
	Set set1("set.txt");
	
	set1.showArr();
	set1.showArrSum();
	set1.showArrMult();

	if (IsField(set1))
		std::cout << "field" << std::endl;
	
	system("pause");
	return 0;
}