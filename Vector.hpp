/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:05:40 by daprovin          #+#    #+#             */
/*   Updated: 2022/02/06 07:49:10 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include "Vector_Iterator.hpp"

template < class T, class Alloc = std::allocator<T> >
class Vector
{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef size_t										size_type;
		typedef	class Iterator<T>							iterator;

	public:
		explicit Vector(void) : _elems(NULL), _first_free(NULL), _end(NULL) {}
		
		explicit Vector(size_type n, const value_type & val = value_type()) : _elems(NULL), _first_free(NULL), _end(NULL)
		{
			reallocate(n);
			for (size_t i = 0; i < n; i++)
				push_back(val);		
		}

		template < class InputIterator >
		explicit Vector(InputIterator first, InputIterator last) : _elems(NULL), _first_free(NULL), _end(NULL)
		{
			for (; first != last; first++)
				push_back(*first);
		}

		Vector(const Vector & x) : _elems(NULL), _first_free(NULL), _end(NULL)
		{
			this->_alloc = x._alloc;
			*this = x;
		}
		
		~Vector(void)
		{
			if (_elems)
			{
				while (_elems != _first_free)
					_alloc.destroy(--_first_free);
				_alloc.deallocate(_elems, capacity());
			}
		}

		Vector &	operator=(const Vector & x)
		{	
			if (this->size() != 0)
				this->clear();
			if (x.size() > this->capacity())
				reallocate(x.size());

			for (size_t i = 0; i < x.size(); i++)
			{
				this->push_back(x[i]);
			}
			return *this;
		}

		//		=========Element Access======

		reference	front(void)
		{
			return *_elems;
		}

		const_reference		front(void) const
		{
			return *_elems;
		}

		reference	back(void)
		{
			return *(_first_free - 1);
		}

		const_reference		back(void) const
		{
			return *(_first_free - 1);
		}

		reference	operator[](size_type n)
		{
			return *(_elems + n);
		}

		const_reference		operator[](size_type n) const
		{
			return *(_elems + n);
		}

		reference	at(size_type n)
		{
			if (n >= size())	
				throw std::out_of_range("vector::_M_range_check");
			else
				return *(_elems + n);
		}

		const_reference		at(size_type n) const
		{
			if (n >= size())	
				throw std::out_of_range("vector::_M_range_check");
			else
				return *(_elems + n);
		}

		//		=========Iterator=========
		
		iterator	begin(void)
		{
			iterator	it(_elems);
			return it;
		}

		iterator	end(void)
		{
			iterator	it(_first_free);
			return	it;
		}

		//		=========Capacity==========

		size_type	size(void)	const
		{
			return (_first_free - _elems);
		}

		size_type	capacity(void) const
		{
			return (_end - _elems);
		}

		size_type	max_size(void) const
		{
			return (_max_size);
		}

		void		resize(size_type n, value_type val = value_type())
		{
			while (n < size())					
				pop_back();
			while (n > size())
				push_back(val);
		}

		bool		empty(void) const
		{
			if (size() == 0)
				return true;
			else
				return false;
		}

		void		reserve(size_type n)
		{
			if (n > _max_size)	
				throw std::length_error("Not enough space");
			else
			{
				if (n > capacity())
					reallocate(n);
			}
		}

		//		========Modifiers========

		void	push_back(const value_type & val)
		{
			if (size() == capacity())
				reallocate();
			_alloc.construct(_first_free, val);
			_first_free++;
		}

		void	pop_back(void)
		{
			if (size() > 0)
				_alloc.destroy(--_first_free);
		}

		void	clear(void)
		{
			while (size() != 0)
				pop_back();
		}

		template < class InputIterator >
		void	assign(InputIterator first, InputIterator end) //must be tested with other iterators
		{
			if (size() != 0)
				clear();
			for (; first != end; first++)
				push_back(*first);
		}

		void	assign(int n, const value_type & val) //si pongo size_t en vez de int no funciona y no se porque
		{
			if (size() != 0)
				clear();
			while (size() < n)
				push_back(val);
		}
		
		iterator	insert(iterator position, const value_type & val) //idk if the return value is good
		{
			if (size() == capacity())
			{
				size_t	oldCapacity = capacity();
				size_t	newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

				pointer	new_elems = _alloc.allocate(newCapacity);
				int		pos = 0;
				if (_elems)
				{
					int	i = 0;
				
					for (iterator first = begin() ; first != position ; i++, first++)	
					{
						_alloc.construct(new_elems + i, _elems[i]);
					}
					pos = i;
					_alloc.construct(new_elems + i, val);
					for (iterator last = end(); last != position; i++, position++)
					{
						_alloc.construct(new_elems + i + 1, _elems[i]);
					}

					while (_elems != _first_free)   //doing free
						_alloc.destroy(--_first_free);
					_alloc.deallocate(_elems, oldCapacity);

				}
				else
					_alloc.construct(new_elems, val);
				_elems = new_elems;
				_first_free = _elems + oldCapacity + 1;
				_end = _elems + newCapacity;
				return (begin() + pos);
			}
			else
			{			
				int			i = 0;
				size_type	s = size();

				for (iterator last = end(); last != position; i++, last--)
				{
					_elems[s - i] = _elems[s - i - 1];
				}
				_elems[s - i] = val;
				_first_free++;
				return (position);
			}
		}

		void	insert(iterator position, size_type n, const value_type & val)
		{
			if (size() + n > capacity()) //lo dejamos por aqui, me voy a desayunar
			{}
			else
			{
				int			i = 0;
				size_type	s = size();
				int			count = 0;

				for (iterator last = end() ; last != position ; i++, last--)
				{
					_elems[s + n - i - 1] = _elems[s - i - 1];
				}
				while (count < n)
				{
					_elems[s + n - i - 1] = val;
					count++;
					i++;
				}
				_first_free = _first_free + n;
			}
		}

	private:
		void	reallocate(void)
		{
			size_t	oldCapacity = capacity();
			size_t	newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;

			pointer	new_elems = _alloc.allocate(newCapacity);
			if (_elems)
			{
				std::uninitialized_copy(_elems, _first_free, new_elems);
				while (_elems != _first_free)
					_alloc.destroy(--_first_free);
				_alloc.deallocate(_elems, oldCapacity);
			}
			_elems = new_elems;
			_first_free = _elems + oldCapacity;
			_end = _elems + newCapacity;
		}

		void	reallocate(size_type n)
		{
			size_t	oldCapacity = capacity();
			size_t	newCapacity = n;

			pointer	new_elems = _alloc.allocate(newCapacity);
			if (_elems)
			{
				std::uninitialized_copy(_elems, _first_free, new_elems);
				while (_elems != _first_free)
					_alloc.destroy(--_first_free);
				_alloc.deallocate(_elems, oldCapacity);
			}
			_elems = new_elems;
			_first_free = _elems + oldCapacity;
			_end = _elems + newCapacity;
		}

	private:
		static std::allocator<T>	_alloc;
		pointer			_first_free;
		pointer			_end;
		pointer			_elems;
		size_type		_max_size = 1073741823;
};

template < typename T, typename Alloc >
std::allocator<T> Vector< T, Alloc >::_alloc;

#endif
