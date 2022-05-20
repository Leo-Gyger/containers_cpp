#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <iostream>
#include <cstddef>
namespace ft
{
	template<typename category, typename T, typename distance = ptrdiff_t, typename p = T* , typename ref = T&>
		struct iterator
		{
			public:
			typedef category	iterator_category;
			typedef T		value_type;
			typedef distance	difference_type;
			typedef p 		pointer;
			typedef ref	reference;
		};
	class random_access_iterator_tag { };
	class input_iterator_tag { };
	class output_iterator_tag { };
	class forward_iterator_tag { };
	class bidrectional_iterator_tag { };
	template  <typename T>
		class	random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		private:
			T*	data;
		public:
			typedef	typename	ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef	typename	ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef	typename	ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef	T*		pointer;
			typedef	T&		reference; 
			random_access_iterator (void)
			{
				return;
			}
			random_access_iterator (T*	ptr) : data(ptr)
			{
				return;
			}
			random_access_iterator	(const random_access_iterator&	it) : data(it.data)
			{
				return;
			}
			~random_access_iterator (void) {}
			typename random_access_iterator::difference_type	operator-(const random_access_iterator&	it)
			{
				return data - it.data;
			}
			random_access_iterator&	operator=(const random_access_iterator&	o)
			{
				data = o.data;
				return (*this);
			}
			random_access_iterator& operator+(int nbr)
			{
				data += nbr;
				return (*this);
			}
			random_access_iterator& operator-(int nbr)
			{
				data -= nbr;
				return (*this);
			}
			random_access_iterator& operator++(int)
			{
				data++;
				return (*this);
			}
			random_access_iterator& operator--(int)
			{
				data--;
				return (*this);
			}
			bool	operator!=(const random_access_iterator&	it)
			{
				if (data != it.data)
					return  true;
				return false;
			}
			bool	operator==(const random_access_iterator&	it)
			{
				return ((this->data == it.data) ? true : false);
			}
			random_access_iterator	operator++()
			{
				random_access_iterator<T> mem;
				mem = *this;
				data++;
				return (mem);
			}
			random_access_iterator	operator--()
			{
				random_access_iterator<T> mem;
				mem = *this;
				data--;
				return (mem);
			}
			T&	operator*()
			{
				return (*data);
			}
	};
	template<typename T>
		typename random_access_iterator<T>::difference_type	distance(random_access_iterator<T> first, random_access_iterator<T> last)
		{
			return last - first;
		}
	template<typename T, typename Distance>
		void	advance(random_access_iterator<T>&	it, Distance n)
		{
			it = it + n;
		}
	template<typename Iterator>
		class reverse_iterator
		{
			private:
			Iterator	iter;
			typedef	Iterator	iterator_type;
			public:
				reverse_iterator(void)
				{
					iter = Iterator();
					return;
				}
				reverse_iterator(iterator_type it) : iter(it)
				{
					return;
				}
				reverse_iterator(const reverse_iterator<Iterator>&	it)
				{
					this->iter = it.iter;
					return;
				}
				reverse_iterator&	operator--()
				{
					Iterator mem;
					mem = this->iter;
					iter++;
					return (mem);
				}
				reverse_iterator&	operator--(int)
				{
					iter++;
					return (*this);
				}
				reverse_iterator	operator++()
				{
					reverse_iterator<Iterator> mem = this->iter;
					mem = this->iter;
					iter--;
					return (mem);
				}
				bool			operator!=(const reverse_iterator<Iterator>&	it)
				{
					if (this->iter != it.iter)
						return true;
					return false;
				}
				reverse_iterator&	operator++(int)
				{
					iter--;
					return (*this);
					
				}
				reverse_iterator&	operator=(const reverse_iterator<Iterator>&	it)
				{
					this->iter = it.iter;
					return (*this);
				}
				typename iterator_type::value_type	operator*()
				{
					return (*iter);
				}
		};
	template<typename iter>
		struct iterator_traits
		{
			typedef typename	iter::difference_type 	difference_type;
			typedef typename 	iter::value_type	value_type;
			typedef typename	iter::pointer		pointer;
			typedef typename	iter::iterator_category	iterator_category;
			typedef typename	iter::reference		reference;
		};
	template<typename iter>
		struct iterator_traits<iter*>
		{
			typedef	ptrdiff_t			difference_type;
			typedef	iter				value_type;
			typedef	iter*				pointer;
			typedef	ft::random_access_iterator_tag	iterator_category;
			typedef iter&				reference;
		};
	template<typename iter>
		struct iterator_traits<const iter*>
		{
			typedef	ptrdiff_t			difference_type;
			typedef	iter				value_type;
			typedef	const iter*				pointer;
			typedef	std::random_access_iterator_tag	iterator_category;
			typedef const iter&				reference;
		};
}
#endif

