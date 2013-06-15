#include "TypeList.h"
#include <iostream>

int main()
{
	static_assert(TypeList<int, double, char>::Length == 3, "Incorrect number of typelist elements!");
	static_assert(std::is_same<TypeAt<2, TypeList<int, double, char>>::Result, char>::value, "TypeAt<TypeList<int, double, char>, 2>::Result is not char!");
	
	return 0;
}
