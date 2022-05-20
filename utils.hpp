#ifndef UTILS_HPP
# define UTILS_HPP
#include "pair.hpp"
#include "iterator.hpp"

namespace	ft
{
	template<typename It>
		typename ft::iterator_traits<It>::difference_type
			distance(It first, It last)
			{
				typename ft::iterator_traits<It>::difference_type rtn = 0;
				while (first != last)
				{
					++first;
					++rtn;
				}
				return rtn;
			}
template<bool condition, typename T = void>
	struct	enable_if {};
template<typename T>
	struct	enable_if<true, T> {
		typedef T	type;
	};

template<typename T>
	struct	is_integral{
		public:
			const static bool	value = false;};
template<>
	struct	is_integral<int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<char>
{
	public:
		const static bool	value = true;
};

template<>
	struct	is_integral<unsigned int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<unsigned char>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<short unsigned int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<short int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<long unsigned int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<long int>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<bool>
{
	public:
		const static bool	value = true;
};
template<>
	struct	is_integral<wchar_t>
{
	public:
		const static bool	value = true;
};

template<typename InputIt1, typename InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return true;
			else if (*first2 < *first1)
				return false;
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}
template<typename InputIt1, typename InputIt2, typename Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
				return true;
			else if (comp(*first2, *first1))
				return false;
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}

}
#endif

