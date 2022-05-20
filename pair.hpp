#ifndef PAIR_HPP
# define PAIR_HPP
namespace	ft
{
	template <typename T1, typename T2>
	struct	pair
	{
		public:
			typedef	T1	first_type;
			typedef	T2	second_type;
			first_type	first;
			second_type	second;
			pair(const first_type&	a, const second_type& b) : first(a), second(b)
			{
			}
			pair() : first(), second()
			{
			}
			template<typename U, typename V>
				pair (const pair<U, V>&	pr) : first(pr.first), second(pr.second)
				{
				}
			pair& operator= (const pair& other)
			{
				first = other.first;
				second = other.second;
				return (*this);
			}
			pair (const pair& p) : first(p.first), second(p.second) {}
			~pair(void)
			{
			}
	};
	template <typename T1, typename T2>
	pair<T1, T2>	make_pair(T1	t, T2	u)
	{
		return (pair<T1, T2>(t, u));
	}
	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first != rhs.first && lhs.second != rhs.second);
	}
	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first < rhs.first && lhs.second < rhs.second);
	}
	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first <= rhs.first && lhs.second <= rhs.second);
	}
	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first > rhs.first && lhs.second > rhs.second);
	}
	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first >= rhs.first && lhs.second >= rhs.second);
	}

}
#endif

