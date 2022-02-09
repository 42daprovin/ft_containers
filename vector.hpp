/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daprovin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:05:40 by daprovin          #+#    #+#             */
/*   Updated: 2022/02/09 04:42:22 by daprovin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>
# include "Vector_Iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"

namespace ft{

	template < class T, class Alloc = std::allocator<T> >
		class vector
		{
			public:
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef size_t										size_type;
				typedef	class ft::iterator<T>							iterator;
				typedef class ft::iterator<const T>						const_iterator;
				typedef	typename iterator_traits<iterator>::difference_type	difference_type;	
				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			public:
				explicit vector(void) : _elems(NULL), _first_free(NULL), _end(NULL) {}

				explicit vector(size_type n, const value_type & val = value_type()) : _elems(NULL), _first_free(NULL), _end(NULL) 
			{
				reallocate(n);
				for (size_t i = 0; i < n; i++)
					push_back(val);		
			}

				template < class InputIterator >
					explicit vector(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) : _elems(NULL), _first_free(NULL), _end(NULL)
				{
					for (; first != last; first++)
						push_back(*first);
				}

				vector(const vector & x) : _elems(NULL), _first_free(NULL), _end(NULL)
			{
				this->_alloc = x._alloc;
				*this = x;
			}

				~vector(void)
				{
					if (_elems)
					{
						while (_elems != _first_free)
							_alloc.destroy(--_first_free);
						_alloc.deallocate(_elems, capacity());
					}
				}

				vector &	operator=(const vector & x)
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

				const_iterator	begin(void) const
				{
					const_iterator	it(_elems);			
					return it;
				}

				iterator	end(void)
				{
					iterator	it(_first_free);
					return	it;
				}

				const_iterator	end(void) const
				{
					const_iterator	it(_first_free);			
					return it;
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
					return (_alloc.max_size());
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
					if (n > max_size())	
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
					void	assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type end) //must be tested with other iterators
					{
						if (size() != 0)
							clear();
						for (; first != end; first++)
							push_back(*first);
					}

				void	assign(size_t n, const value_type & val)
				{
					if (size() != 0)
						clear();
					while (size() < n)
						push_back(val);
				}

				iterator	erase(iterator position)
				{
					iterator	tmp = position;

					for (iterator last = end() ; position < last ; position++)
					{
						*position = *(position + 1);	
					}
					pop_back();
					return tmp;
				}

				iterator	erase(iterator first, iterator last)
				{
					iterator	tmp_1 = first;
					iterator	tmp_2 = last;

					for ( ; tmp_2 < end() ; tmp_1++, tmp_2++)
					{
						*tmp_1 = *tmp_2;	
					}

					for ( ; first != last && first != end() ; first++)
					{
						pop_back();
					}
					return (last - 1);
				}

				void	swap(vector & x)	
				{

					pointer		tmp = this->_elems;
					size_t		v_size = size();
					size_t		v_capacity = capacity();
					this->_elems = x._elems;
					this->_first_free = x._first_free;
					this->_end = x._end;

					x._elems = tmp;	
					x._first_free = x._elems + v_size;
					x._end = x._elems + v_capacity;
				}

				//======================Insert===========================

				iterator	insert(iterator position, const value_type & val) //idk if the return value is good
				{
					if (size() == capacity())
					{
						size_t	oldCapacity = capacity();
						size_t	newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;
						size_t	c_size = size();

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
						_first_free = _elems + c_size + 1;
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
					if (size() + n > capacity())
					{
						size_t	oldCapacity = capacity();
						size_t	newCapacity = oldCapacity + n;
						size_t	c_size = size();

						pointer	new_elems = _alloc.allocate(newCapacity);
						if (_elems)
						{
							size_type i = 0;

							for (iterator first = begin() ; first != position ; i++, first++)
							{
								_alloc.construct(new_elems + i, _elems[i]);
							}
							for (size_type j = 0 ; j < n ; j++)
							{
								_alloc.construct(new_elems + i + j, val);
							}
							for (iterator last = end() ; last != position ; i++, position++) //si la posicion esta out of range pasan cositas seguramente
							{
								_alloc.construct(new_elems + i + n, _elems[i]);
							}

							while (_elems != _first_free)
								_alloc.destroy(--_first_free);
							_alloc.deallocate(_elems, oldCapacity);
						}
						else
						{
							for (size_type j = 0 ; j < n ; j++)
							{
								_alloc.construct(new_elems + j, val);
							}
						}

						_elems = new_elems;
						_first_free = _elems + c_size + n;
						_end = _elems + newCapacity;
					}
					else
					{
						size_type	i = 0;
						size_type	s = size();
						size_type	count = 0;

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

				template < class InputIterator >
					void	insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
					{
						size_t			insert_size = 0;	
						
						for(InputIterator tmp = first ; tmp != last ; tmp++)
							insert_size++;
						std::cout << "Holaaaaa: "<< *first << std::endl;
						std::cout << "Holaaaaa: "<< insert_size << std::endl;

						if (size() + insert_size > capacity())
						{
							size_t	oldCapacity = capacity();	
							size_t	newCapacity	= oldCapacity + insert_size;
							size_t	c_size = size();

							pointer		new_elems = _alloc.allocate(newCapacity);
							if (_elems)
							{
								size_type i = 0;

								for (iterator beg = begin() ; beg != position ; i++, beg++)
								{
									_alloc.construct(new_elems + i, _elems[i]);
								}
								for (size_type j = 0 ; first != last ; first++, j++)
								{
									_alloc.construct(new_elems + i + j, *first);
								}
								for (iterator last = end() ; last != position ; i++, position++)
								{
									_alloc.construct(new_elems + i + insert_size, _elems[i]);
								}

								while (_elems != _first_free)
									_alloc.destroy(--_first_free);

							}
							else
							{
								for (size_type j = 0 ; first != last ; first++, j++)
								{
									_alloc.construct(new_elems + j, *first);
								}
							}

							_elems = new_elems;
							_first_free = _elems + c_size + insert_size;
							_end = _elems + newCapacity;
						}
						else
						{
							size_type	i = 0;
							size_type	s = size();
							size_type	count = 0;

							for (iterator last = end() ; last != position ; i++, last--)
							{
								_elems[s + insert_size - i - 1] = _elems[s - i - 1];
							}
							while (first != last--)
							{
								_elems[s + insert_size - i - 1] = *last;
								count++;
								i++;
							}
							_first_free = _first_free + insert_size;
						}

					}

				//=========allocator getter============

				allocator_type	get_allocator(void) const
				{
					return this->_alloc;
				}

			private:
				void	reallocate(void)
				{
					size_t	oldCapacity = capacity();
					size_t	newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;
					size_t	c_size = size();

					pointer	new_elems = _alloc.allocate(newCapacity);
					if (_elems)
					{
						std::uninitialized_copy(_elems, _first_free, new_elems);
						while (_elems != _first_free)
							_alloc.destroy(--_first_free);
						_alloc.deallocate(_elems, oldCapacity);
					}
					_elems = new_elems;
					_first_free = _elems + c_size;
					_end = _elems + newCapacity;
				}

				void	reallocate(size_type n)
				{
					size_t	oldCapacity = capacity();
					size_t	newCapacity = n;
					size_t	c_size = size();

					pointer	new_elems = _alloc.allocate(newCapacity);
					if (_elems)
					{
						std::uninitialized_copy(_elems, _first_free, new_elems);
						while (_elems != _first_free)
							_alloc.destroy(--_first_free);
						_alloc.deallocate(_elems, oldCapacity);
					}
					_elems = new_elems;
					_first_free = _elems + c_size;
					_end = _elems + newCapacity;
				}

			private:
				static std::allocator<T>	_alloc;
				pointer			_elems;
				pointer			_first_free;
				pointer			_end;
		};

	template < typename T, typename Alloc >
		std::allocator<T> vector< T, Alloc >::_alloc;

}
#endif
