#include <cstddef>

template <typename... List>
struct TypeList
{
	enum
	{
		Length = sizeof...(List)
	};
};

template <size_t i, typename Head, typename... Tail> struct TypeAt;

template <size_t i, typename Head, typename... Tail>
struct TypeAt<i, TypeList<Head, Tail...>>
{
	static_assert(i < TypeList<Head, Tail...>::Length, "Index passed to TypeAt is out of range for type list!");
	typedef typename TypeAt<i - 1, TypeList<Tail...>>::Result Result; 
};

template <typename Head, typename... Tail>
struct TypeAt<0, TypeList<Head, Tail...>>
{
	typedef Head Result;
};


