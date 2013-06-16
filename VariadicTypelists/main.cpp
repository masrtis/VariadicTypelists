#include "TypeList.h"
#include <iostream>

int main()
{
	static_assert(TypeList<int, double, char>::Length == 3, "Incorrect number of typelist elements!");
	static_assert(std::is_same<TypeAt<2, TypeList<int, double, char>>::Result, char>::value, "TypeAt<TypeList<int, double, char>, 2>::Result is not char!");
	static_assert(IndexOf<float, TypeList<int, double, char>>::value == -1, "Found type that is not in typelist!");
	static_assert(IndexOf<int, TypeList<int, double, char>>::value == 0, "Did not find int in TypeList<int, double, char>");
	static_assert(IndexOf<char, TypeList<int, double, char>>::value == 2, "Did not find char in TypeList<int, double, char>");
	
	return 0;
}
