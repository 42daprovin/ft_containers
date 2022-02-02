/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:05:40 by daprovin          #+#    #+#             */
/*   Updated: 2022/02/02 01:11:08 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>

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

	public:
		Vector(void) : _elems(NULL), _first_free(NULL), _end(NULL) {}
		~Vector(void)
		{
			if (_elems)
			{
				while (_elems != _first_free)
					_alloc.destroy(--_first_free);
				_alloc.deallocate(_elems, capacity());
			}
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

		value_type &	operator[](size_type n)
		{
			return(_elems[n]);
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

	private:
		static std::allocator<T>	_alloc;
		pointer			_first_free;
		pointer			_end;
		pointer			_elems;
};

template < typename T, typename Alloc >
std::allocator<T> Vector< T, Alloc >::_alloc;

#endif
