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

template <typename ToFind, typename Head, typename... Tail>
struct IndexOf;

template <typename ToFind>
struct IndexOf<ToFind, TypeList<>>
{
	enum
	{
	    value = -1
	};
};

template <typename ToFind, typename... Tail>
struct IndexOf<ToFind, TypeList<ToFind, Tail...>>
{
	enum
	{
	    value = 0
	};
};

template <typename ToFind, typename Head, typename... Tail>
struct IndexOf<ToFind, TypeList<Head, Tail...>>
{
private:
	enum
	{
	    checkNextElement = IndexOf<ToFind, TypeList<Tail...>>::value
	};
public:
	enum
	{
	    value = checkNextElement == -1 ? -1 : 1 + checkNextElement
	};
};
