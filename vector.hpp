#pragma once

#include <iostream>
#include <cmath>
#include "iterator.hpp"
#include "utils.hpp"
#include <functional>
namespace ft
{
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef				T						value_type;
			typedef				Allocator					allocator_type;
			typedef				std::size_t					size_type;
			typedef				std::ptrdiff_t					difference_type;
			typedef				value_type&					reference;
			typedef			const	value_type&					const_reference;
			typedef	typename		Allocator::pointer				pointer;
			typedef	typename		Allocator::const_pointer			const_pointer;
			typedef				ft::random_access_iterator<value_type>		iterator;
			typedef				ft::random_access_iterator<const value_type>	const_iterator;
			typedef				ft::reverse_iterator<iterator>			reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			size_type	nbr_elements;
			size_type	allocated_elements;
      			Allocator	Alloc;
			value_type	*data;
		public:
			vector() : nbr_elements(0)
			{
				Alloc = Allocator();
				allocated_elements = 0;
				data = NULL;
			}
			explicit	vector(const	Allocator&	alloc) : Alloc(alloc)
			{
				data = NULL;
				allocated_elements = 0;
				nbr_elements = 0;
			}
			explicit vector(size_type	count, const T&	value = T(), const Allocator&	alloc = Allocator())
			{
				Alloc = alloc;
				data = Alloc.allocate(count);
				allocated_elements = count;
				for (nbr_elements = 0; nbr_elements != count; ++nbr_elements)
					Alloc.construct(&data[nbr_elements], value);
			}
			vector(iterator first, iterator last, const Allocator& alloc = Allocator() ) : Alloc(alloc)
			{
				difference_type	diff = ft::distance(first, last);
				data = Alloc.allocate(diff);
				allocated_elements = diff;
				value_type	*ret = data;
				while (diff--)
				{
					Alloc.construct(ret, *first++);
					ret++;
					nbr_elements++;
				}
			}

			vector	(const vector& ot) : allocated_elements(ot.allocated_elements), Alloc(ot.Alloc)
			{
				data = Alloc.allocate(allocated_elements);
				for (nbr_elements = 0; nbr_elements != ot.nbr_elements; ++nbr_elements)
					Alloc.construct(&data[nbr_elements], ot.data[nbr_elements]);
			}

			vector&	operator= (const vector& other)
			{
				for (size_type i = 0; i != nbr_elements; ++i)
					Alloc.destroy(&data[i]);
				Alloc.deallocate(data, allocated_elements);
				allocated_elements = other.allocated_elements;
				Alloc = other.Alloc;
				data = Alloc.allocate(allocated_elements);
				for (nbr_elements = 0; nbr_elements != other.nbr_elements; ++nbr_elements)
					data[nbr_elements] = other.data[nbr_elements];
				return (*this);
			}
			void	reserve(size_type new_cap)
			{
				if (new_cap <= allocated_elements)
					return;
				value_type	*ndata;
				ndata = Alloc.allocate(new_cap);
				if (nbr_elements != 0)
				{
					for (size_type i = 0; i != nbr_elements; ++i)
						ndata[i] = T(data[i]);
					Alloc.deallocate(data, allocated_elements);
				}
				allocated_elements = new_cap;
				data = ndata;
			}

			void	push_back(const T& value)
			{
				//std::cout << nbr_elements << " " << allocated_elements << std::endl;
				if (nbr_elements + 1 >= allocated_elements)
				{
					if (nbr_elements == 0)
						reserve(nbr_elements + 1);
					else
					reserve(nbr_elements * 2);
				}
				Alloc.construct(&data[nbr_elements], value);
				++nbr_elements;
			}
			size_type	size() const
			{
				return (this->nbr_elements);
			}
			
			size_type	max_size(void) const
			{
				return (Alloc.max_size());
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n > size())
				{
					for ( ; nbr_elements != n; ++nbr_elements)
						push_back(val);
				}
				if (n < size())
				{
					for ( ; nbr_elements != n; --nbr_elements)
						Alloc.destroy(&data[nbr_elements - 1]);
				}
			}

			size_type	capacity(void) const
			{
				return (this->allocated_elements);
			}

			bool	empty() const
			{
				if (nbr_elements == 0)
					return (true);
				return (false);
			}

			reference	operator[] (size_type n)
			{
				return (data[n]);
			}

			const_reference	operator[] (size_type n) const
			{
				return (data[n]);
			}

			void	swap(vector&	x)
			{
				value_type	*ret = data;
				size_type 	capa = allocated_elements;
				size_type	nbr_elem = nbr_elements;

				data = x.data;
				allocated_elements = x.allocated_elements;
				nbr_elements = x.nbr_elements;

				x.data = ret;
				x.allocated_elements = capa;
				x.nbr_elements = nbr_elem;
				
			}

			reference at (size_type n)
			{
				if (n >= nbr_elements)
					throw std::out_of_range("Index out of bound");
				else
					return (data[n]);
			}

			reference	front()
			{
				return (data[0]);
			}
			template<typename InputIt>
			void assign(InputIt first, InputIt last)
			{
				clear();
				insert(&data[0], first, last);
			}
			const_reference	front() const
			{
				return (data[0]);
			}

			reference	back()
			{
				return (data[nbr_elements - 1]);
			}

			const_reference	back() const
			{
				return (data[nbr_elements - 1]);
			}
			reverse_iterator	rbegin()
			{
				return (&data[nbr_elements - 1]);
			}
			const_reverse_iterator	rbegin() const
			{
				return (&data[nbr_elements - 1]);
			}
			const_reverse_iterator	rend() const
			{
				return (&data[-1]);
			}
			reverse_iterator	rend()
			{
				return (&data[-1]);
			}
			iterator	begin()
			{
				return (&data[0]);
			}
			const_iterator	begin() const
			{
				return (&data[0]);
			}
			void	pop_back()
			{
				--nbr_elements;
				Alloc.destroy(&data[nbr_elements]);
			}
			iterator	insert(iterator	position, const value_type&	val)
			{
				size_type	i = 0;
				if (nbr_elements > allocated_elements)
				{
					allocated_elements = std::exp(allocated_elements);
					reserve(allocated_elements);
				}
				value_type	*ndata = Alloc.allocate(allocated_elements);
				for (i = 0; begin() + i != position; ++i)
					ndata[i] = data[i];
				Alloc.construct(&ndata[i], val);
				iterator	ret = &ndata[i];
				for ( ; i != nbr_elements; ++i)
				{
					ndata[i + 1] = data[i];
				}
				Alloc.deallocate(data, allocated_elements);
				data = ndata;
				++nbr_elements;
				return (ret);

			}
			void	assign(size_type	n, const value_type& val)
			{
				clear();
				for	( ; nbr_elements != n; ++nbr_elements)
						push_back(val);
			}
			void	insert(iterator	position, size_type	n, const value_type&	val)
			{
				size_type	i = 0;
				if (nbr_elements + n > allocated_elements)
				{
					allocated_elements = std::exp(allocated_elements);
					reserve(allocated_elements);
				}
				value_type	*ndata = Alloc.allocate(allocated_elements);
				for (i = 0; begin() + i != position; ++i)
					ndata[i] = data[i];
				for (size_type a = 0; a != n; ++a)
					Alloc.construct(&ndata[i + a], val);
				for ( ; i != nbr_elements; ++i)
				{
					ndata[i + n] = data[i];
				}
				Alloc.deallocate(data, allocated_elements);
				data = ndata;
				nbr_elements += n;
				return (&data[0]);

			}
			template <typename InputIterator>
				void	insert(iterator	position, InputIterator first, InputIterator last)
			{
				size_type	i = 0;
				difference_type	n = ft::distance(first, last);
				if (nbr_elements + n > allocated_elements)
				{
					allocated_elements = std::exp(allocated_elements);
					reserve(allocated_elements);
				}
				value_type	*ndata = Alloc.allocate(allocated_elements);
				for (i = 0; begin() + i != position; ++i)
					ndata[i] = data[i];
				for (difference_type a = 0; a != n; ++a)
				{
					Alloc.construct(&ndata[i + a], *first);
					++first;
				}
				for ( ; i != nbr_elements; ++i)
				{
					ndata[i + n] = data[i];
				}
				Alloc.deallocate(data, allocated_elements);
				data = ndata;
				nbr_elements += n;
			}
			iterator	end(void)
			{
				return (&data[nbr_elements]);
			}
			const_iterator	end(void) const
			{
				return (&data[nbr_elements]);
			}
			iterator	erase(iterator	position)
			{
				difference_type	pos = ft::distance(begin(), position);
				value_type		*ndata = Alloc.allocate(allocated_elements);
				for (size_type	i = 0; i != nbr_elements; ++i)
					ndata[i] = data[i];
				Alloc.destroy(&data[pos]);
				for ( ; pos < (difference_type)nbr_elements - 1; ++pos)
					data[pos] = ndata[pos + 1];
				Alloc.deallocate(ndata, allocated_elements);
				--nbr_elements;
				return (position);
			}
			iterator	erase(iterator	first, iterator last)
			{
				difference_type	pos,end;
				pos = ft::distance(begin(), first);
				end = ft::distance(begin(), last);
				while (pos != end)
				{
					erase(first);
					++pos;
				}
				return (&data[0]);
			}
			void	clear()
			{
				while (nbr_elements != 0)
				{
					--nbr_elements;
					Alloc.destroy(&data[nbr_elements]);
				}
			}


			~vector(void)
			{
				clear();
				Alloc.deallocate(data, capacity());
			}
	};
		template<typename T, class Alloc>
			bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				if (!(lhs.size() == rhs.size()))
					return false;
				for (size_t i = 0; i != lhs.size(); ++i)
				{
					if (!(lhs[i] == rhs[i]))
						return false;
				}
				return true;
			}
		template<typename T, class Alloc>
			bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				if (!(lhs.size() == rhs.size()))
					return true;
				for (size_t i = 0; i < lhs.size(); ++i)
				{
					if (!(lhs[i] != rhs[i]))
						return false;
				}
				return true;
			}
  template<typename T, class Alloc>
			bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
		template<typename T, class Alloc>
			bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<T>());
			}
		template<typename T, class Alloc>
			bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater_equal<T>());
			}
		template<typename T, class Alloc>
			bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
			{
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater<T>());
			}
}
