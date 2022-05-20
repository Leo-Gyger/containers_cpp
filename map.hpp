#ifndef MAP_HPP
#define MAP_HPP
#include "pair.hpp"
#include "bst.hpp"
#include "utils.hpp"
namespace ft
{
  template<typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<Key,T> > >
  class map
  {
    public:
    typedef Key key_type;
    typedef T   mapped_type;
    typedef ft::pair<Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;
    typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;

    private:
    class value_compare : std::binary_function<value_type, value_type, bool>
    {
      friend class map<key_type, mapped_type, key_compare, Allocator>;
      protected:
      Compare comp;
      value_compare(Compare c) : comp(c) {}
      public:

      bool operator() (const value_type&x, const value_type& y) const
        {
          return (comp(x.first, y.first));
        }
    };
    ft::Binary_search_tree<value_type, key_compare> tree;
    Compare comp;
    Allocator alloc;
    public:
    map() : tree(), comp(Compare ()), alloc() {}
    explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : tree(alloc), comp(comp), alloc() {}
    template <typename Inputit>
    map(Inputit first, Inputit last, const key_compare& comp = key_compare(), const allocator_type& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<Inputit>::value, Inputit>::type = 0) : tree(), comp(comp), alloc(alloc)
    {
      insert(first, last);
    }
    map(map& m) : tree(), comp(m.comp), alloc(m.alloc)
    {
      insert<iterator>(m.begin(), m.end());
    }
    ~map()
    {
     clear();
    }
    map& operator=(const map& o)
    {
	   if (&o == this)
		   return *this;
	   this->clear();
	   this->insert(o.begin(), o.end());
	   return (*this);
    }
    void clear ()
    {
        erase(begin(), end());
    }
    iterator begin()
    {
      return (iterator(tree._last_node->left, tree._last_node));
    }
    const_iterator begin() const
    {
      return (const_iterator(tree._last_node->left, tree._last_node));
    }
    iterator end()
    {
      return (iterator(tree._last_node, tree._last_node));
    }
    const_iterator end() const
    {
      return (const_iterator(tree._last_node, tree._last_node));
    }
    ft::pair<iterator, bool> insert (const value_type& val)
    {
      return (tree.insertPair(val));
    }
    iterator insert(iterator pos, const value_type& val)
    {
      (void)pos;
      return (tree.insertPair(val).first);
    }
    template<typename Inputit>
    void insert(Inputit first, Inputit last, typename ft::enable_if<!ft::is_integral<Inputit>::value, Inputit>::type* = 0)
      {
        difference_type  n = ft::distance(first, last);
        while(n--)
          this->insert(*(first++));
      }
    iterator find(const key_type& k)
      {
        return (iterator(tree.searchByKey(ft::make_pair(k, mapped_type())), tree._last_node));
      }
    const_iterator find(const key_type& k) const
      {
        return (const_iterator(tree.searchByKey(ft::make_pair(k, mapped_type())), tree._last_node));
      }
    T& operator[] (const Key& k)
      {
        iterator it = find(k);
        if (it == end())
          this->insert(ft::make_pair(k, mapped_type()));
        it = this->find(k);
        return ((*it).second);
      }
    bool empty() const
      {
        return (tree._last_node->parent == tree._last_node);
      }
    size_type max_size() const
      {
        return (tree.max_size());
      }
    size_type size() const
      {
        return tree._last_node->value.first;
      }
    size_type count(const Key& key) const
      {
        if (find(key) == end())
          return 0;
        else
          return 1;
      }
    iterator lower_bound(const Key& k)
      {
        iterator beg = begin();
        iterator en = end();
        while (beg != en)
          {
            if (comp((*beg).first, k) == 0)
              break;
            ++beg;
          }
        return beg;
      }
    const_iterator lower_bound(const Key& k) const
      {
        return (const_iterator(lower_bound(k)));
      }
    iterator upper_bound(const Key& k)
      {
        iterator beg = begin();
        iterator en = end();
        while (beg != en)
          {
            if (comp(k, (*beg).first))
              break;
            ++beg;
          }
        return beg;
      }
    size_type erase(const key_type& k)
      {
        if (this->find(k) == this->end())
          return 0;
        else
          tree.removeByKey(ft::make_pair(k, mapped_type()));
        return 1;
      }
    void erase(iterator f, iterator l)
      {
        while (f != l)
          this->erase((*(f++)).first);
      }
    void erase(iterator pos)
      {
        this->erase(pos.first);
      }
    void swap (map& x)
      {
        tree.swap(x.tree);
      }
    const_iterator upper_bound(const Key& k) const
      {
        return (const_iterator(upper_bound(k)));
      }
    ft::pair<iterator, iterator> equal_range(const Key& key)
      {
        return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
      }
    ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
      {
        return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
      }
    key_compare key_comp() const
      {
        return comp;
      }
    value_compare value_comp() const
      {
        return value_compare();
      }


  };
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
      if (lhs.size() != rhs.size())
        return false;
      typename ft::map<Key, T, Compare, Alloc>::const_iterator it1, it2;
      it1 = lhs.begin();
      it2 = rhs.begin();
      while (it1 != lhs.end() && it2 != rhs.end())
        {
          if (*it1 != *it2)
            return false;
		  ++it1;
		  ++it2;
        }
      return true;
    }
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
      if (lhs.size() != rhs.size())
        return true;
      typename ft::map<Key, T, Compare, Alloc>::const_iterator it1, it2;
      it1 = lhs.begin();
      it2 = rhs.begin();
      while (it1 != lhs.end() && it2 != rhs.end())
        {
          if (*it1 != *it2)
            return true;
		  ++it1;
		  ++it2;
        }
      return false;
    }
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
     return (ft::lexicographical_compare<ft::map<Key, T, Compare, Alloc>::iterator, ft::map<Key, T, Compare, Alloc>::iterator> (lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater<Key>()));
    }
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
     return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::greater_equal<Key>()));
    }
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
     return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less<Key>()));
    }
  template <typename Key, typename T, typename Compare, typename Alloc>
  bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
    {
     return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::less_equal<Key>()));
    }
}
#endif
