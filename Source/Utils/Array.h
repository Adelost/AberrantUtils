#pragma once

#include "Cast.h"
#include "Memory.h"
#include "XAssert.h"

namespace ae
{
	/** Dynamic array implementation.

		It stores its items in adjacent memory locations and provides fast
		index-based access. It does not allocate memory until an element is added to
		it.

		Provides out of bound checking in debug. Supports C++11 iterators to make
		iterating more convenient. Allows adding multiple elements on a single line
		using the output stream operator. */
	template<class T> class Array
	{
	public:
		/** Constructs an empty container. */
		Array();
		/** Constructs a Array with an initial size of "size" elements constructed
			using default constructor. */
		Array(int size);
		/** Constructs a copy of "other". */
		Array(const Array<T>& other);
		/** Destroys the container and all elements. */
		~Array();

		/** Copies the elements of "other" to this container, replacing its current
			contents, and modifying its size accordingly. */
		Array<T>& operator=(const Array<T>& other);
		/** Same as add(), overloading stream operator allows adding multiple
			elements. */
		Array<T>& operator<<(const T& element);
		/** Returns element at the specified index. */
		T& operator[](int index);
		const T& operator[](int index) const;

		/** Adds an element to the container. */
		void add(const T& element);
		/** Adds multiple element to the container from a pointer to an array. */
		void add(const T* elements, int count);
		/** Adds uninitialized elements to the container (see also resize()). */
		void addEmpty(int size = 1);
		/** Inserts an element at specified index. Subsequent elements are
			transposed to cover the resulting gap, which may be a slow operation
			depending of the number of elements. */
		void addAt(int index, const T& element);
		/** Same as addAt() but allows adding multiple elements. */
		void addAt(int index, const T* elements, int count);
		/** Removes the last element. */
		void removeLast();
		/** Removes element at index. Subsequent elements are transposed to cover
			the resulting gap. See also addAt(). */
		void removeAt(int index);
		/** Same as removeAt() but allows removing multiple elements. */
		void removeAt(int index, int count);
		/** Fast removal of element by swapping the last element with the element
			deleted. */
		void swapRemove(int index);
		/** Removes all elements (which are destroyed) from container. */
		void clear();
		/** Same as clear() but also releases any allocated memory. */
		void clearMemory();
		/** If "size" exceeds capacity, more memory is allocated until capacity is
			enough to hold "size" elements. */
		void reserve(int size);
		/** Same as reserve(), except that the growth in capacity is limitied to
			exactly "size" elements. This allows saving memory in some situation. */
		void reserveExact(int size);
		/** Resized the container so that it contains "size" elements. New
			elements are uninitialized. */
		void resize(int size);
		/** Returns the index of an element inside the container. Element must
			already be residing inside the container. Useful in some rare
			situations where an element do not know its index. */
		int indexFromElement(T* element);

		/** Returns the first item. */
		T& first();
		const T& first() const;
		/** Returns the last item. */
		T& last();
		const T& last() const;
		/** Exposes the raw pointer storing the data of the container. The pointer
			can be used to modify elements and remains valid as long as the
			container is not reallocated. */
		T* raw();
		const T* raw() const;
		/** Returns the number of stored elements. */
		int count() const;
		/** Returns the number of elements the array can contain
		before needing to resize. */
		int capacity() const;
		/** Returns true if array contains no elements. */
		bool isEmpty() const;
		/** Returns true if adding another element will cause the array to resize. */
		bool isFull() const;
		/** Checks if "index" is within the boundaries of the array. */
		bool isInside(int index) const;

	private:
		T* m_elements;
		int m_count;
		int m_capacity;

	public:
		#pragma region Iterator
		class Iterator
		{
		public:
			Iterator(Array* host, int index)
			{
				m_host = host;
				m_index = index;
			}
			void reset()
			{
				m_index = 0;
			}
			bool operator!=(const Iterator& other) const
			{
				return m_index != other.m_index;
			}
			const Iterator& operator++()
			{
				m_index++;

				return *this;
			}
			T& operator*() const
			{
				return (*m_host)[m_index];
			}

		private:
			Array* m_host;
			int m_index;

		};
		Iterator begin()
		{
			return Iterator(this, 0);
		}
		Iterator end()
		{
			return Iterator(this, m_count);
		}
		#pragma endregion
	};

	template<class T>
	Array<T>::Array()
	{
		m_elements = nullptr;
		m_count = 0;
		m_capacity = 0;
	}

	template<class T>
	Array<T>::Array(const Array<T>& other) : Array()
	{
		*this = other;
	}

	template<class T>
	Array<T>::Array(int size)
	{
		m_elements = new T[size];
		m_count = size;
		m_capacity = size;
	}

	template<class T>
	Array<T>::~Array()
	{
		clearMemory();
	}

	template<class T>
	void Array<T>::addEmpty(int count)
	{
		resize(m_count + count);
	}

	template<class T>
	void Array<T>::add(const T& element)
	{
		reserve(m_count + 1);
		Memory::place(element, m_elements[m_count]);
		m_count++;
	}

	template<class T>
	void Array<T>::add(const T* elements, int count)
	{
		reserve(m_count + count);
		for (int i = 0; i < count; i++)
			Memory::place(elements[i], m_elements[m_count + i]);
		m_count += count;
	}

	template<class T>
	Array<T>& Array<T>::operator<<(const T& element)
	{
		add(element);

		return *this;
	}

	template<class T>
	void Array<T>::addAt(int index, const T& element)
	{
		addAt(index, &element, 1);
	}

	template<class T>
	void Array<T>::addAt(int index, const T* elements, int count)
	{
		// Shift elements right to create a gap
		reserve(m_count + count);
		int size = m_count - index;
		Memory::move(&m_elements[index], &m_elements[index + count], size);

		// Add elements
		for (int i = 0; i < count; i++)
			Memory::place(elements[i], m_elements[index + i]);
		m_count += count;
	}

	template<class T>
	void Array<T>::removeLast()
	{
		xassert_msg(!isEmpty(), "No elements to remove.");
		last().~T();
		m_count--;
	}

	template<class T>
	void Array<T>::removeAt(int index)
	{
		removeAt(index, 1);
	}

	template<class T>
	void Array<T>::removeAt(int index, int count)
	{
		xassert_msg(m_count - count >= 0, "No elements to remove.");

		// Remove elements
		for (int i = 0; i < count; i++)
			m_elements[index + i].~T();
		m_count -= count;

		// Shift right segment left to cover gap
		int rightSize = m_count - index;
		Memory::move(&m_elements[index + count], &m_elements[index], rightSize);
	}

	template<class T>
	void Array<T>::swapRemove(int index)
	{
		xassert_msg(!isEmpty(), "No elements to remove.");
		m_elements[index].~T();
		Memory::copy(&m_elements[m_count - 1], &m_elements[index], 1);
		m_count--;
	}

	template<class T>
	Array<T>& Array<T>::operator=(const Array<T>& other)
	{
		clear();
		add(other.raw(), other.count());

		return *this;
	}

	template<class T>
	void Array<T>::clear()
	{
		for (int i = count() - 1; i >= 0; i--)
			m_elements[i].~T();
		m_count = 0;
	}

	template<class T>
	void Array<T>::clearMemory()
	{
		clear();

		Memory::deallocateRaw(m_elements);
		m_elements = nullptr;
		m_capacity = 0;
	}

	template<class T>
	T& Array<T>::operator[](int index)
	{
		return CALL_CONST_METHOD_AS_NON_CONST(operator[](index));
	}

	template<class T>
	const T& Array<T>::operator[](int index) const
	{
		xassert_msg(isInside(index), "Index out of bounds.");

		return m_elements[index];
	}

	template<class T>
	T& Array<T>::first()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(first());
	}

	template<class T>
	const T& Array<T>::first() const
	{
		return (*this)[0];
	}

	template<class T>
	T& Array<T>::last()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(last());
	}

	template<class T>
	const T& Array<T>::last() const
	{
		return (*this)[m_count - 1];
	}

	template<class T>
	T* Array<T>::raw()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(raw());
	}

	template<class T>
	const T* Array<T>::raw() const
	{
		return m_elements;
	}

	template<class T>
	int Array<T>::count() const
	{
		return m_count;
	}

	template<class T>
	int Array<T>::capacity() const
	{
		return m_capacity;
	}

	template<class T>
	bool Array<T>::isEmpty() const
	{
		return m_count == 0;
	}

	template<class T>
	bool Array<T>::isFull() const
	{
		return m_count >= m_capacity;
	}

	template<class T>
	void Array<T>::reserve(int size)
	{
		if (size > m_capacity)
		{
			if (m_capacity < 1)
				m_capacity = 1;
			while (m_capacity < size)
				m_capacity *= 2;

			T* tmp = Memory::allocateRaw<T>(m_capacity);
			Memory::copy(&m_elements[0], &tmp[0], m_count);
			Memory::deallocateRaw(m_elements);
			m_elements = tmp;
		}
	}

	template<class T>
	void Array<T>::reserveExact(int size)
	{
		if (size > m_capacity)
		{
			m_capacity = size;

			T* tmp = Memory::allocateRaw(m_capacity);
			Memory::copy(m_elements[0], tmp[0], m_count);
			Memory::deallocateRaw(m_elements);
			m_elements = tmp;
		}
	}

	template<class T>
	void Array<T>::resize(int size)
	{
		if (size > m_count)
		{
			reserve(size);

			for (int i = m_count; i < m_count; i++)
				Memory::place(T(), m_elements[i]);

			m_count = size;
		}
	}

	template<class T>
	int indexFromElement(T* element)
	{
		int index = static_cast<int>(&m_values[0] - &value);
		xassert_msg(isInside(index), "Element do not reside inside container.");

		return index;
	}

	template<class T>
	bool Array<T>::isInside(int index) const
	{
		return index >= 0 && index < count();
	}
}