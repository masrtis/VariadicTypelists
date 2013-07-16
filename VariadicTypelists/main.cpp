#include "TypeList.h"
#include <iostream>

int main()
{
	typedef TypeList<int, double, char> Types;
	
	static_assert(Types::Length == 3, "Incorrect number of typelist elements!");

	static_assert(std::is_same<TypeAt<2, Types>::Result, char>::value, "TypeAt<TypeList<int, double, char>, 2>::Result is not char!");

	static_assert(IndexOf<float, Types>::value == -1, "Found type that is not in typelist!");
	static_assert(IndexOf<int, Types>::value == 0, "Did not find int in TypeList<int, double, char>");
	static_assert(IndexOf<char, Types>::value == 2, "Did not find char in TypeList<int, double, char>");

	static_assert(Append<int, TypeList<>>::Result::Length == 1, "Did not append int to empty typelist");
	static_assert(Append<float, Types>::Result::Length == 4, "Did not append float to TypeList<int, double, char>");
	static_assert(Append<Types, TypeList<float, double>>::Result::Length == 5, "Did not append TypeList<char, short, int> to TypeList<float, double>");

	static_assert(Erase<int, Types>::Result::Length == 2, "Did not erase int from TypeList<int, double, char>");
	static_assert(Erase<double, Types>::Result::Length == 2, "Did not erase double from TypeList<int, double, char>");

	return 0;
}
