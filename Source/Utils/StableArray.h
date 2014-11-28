#pragma once

#include "Array.h"

namespace ae
{
	/** A container similar to a dynamic-array, but which do not reallocate the
		memory address of the stored elements when growing. It provides a fast
		index-based access. However, elements are allocated in segments and are not
		guaranteed to be stored in adjacent memory locations.

		At the moment it only allows allocating uninitialized elements in which
		initialized elements can be copied into. */
	template<class T>
	class StableArray
	{
	public:
		StableArray()
		{
			m_nextPoolSize = 1;
		}

		~StableArray()
		{
			// Release all allocated pools
			for (T* p : m_pools)
				delete[] p;
		}

		/** Make sure container can hold "size" number of elements without needing
			allocate more memory. */
		void resize(int size)
		{
			reserve(size);
			m_count = size;
		}

		/** If "size" exceeds capacity, more memory is allocated until capacity is
			enough to hold "size" elements. */
		void reserve(int size)
		{
			if (size > capacity())
			{
				// Increment capacity by adding pools of increasing sizes until
				// "size" is reached
				while (capacity() < size)
				{
					// Add pool
					T* pool = (T*) new char[m_nextPoolSize * sizeof(T)];
					m_pools.add(pool);

					// Add elements from pool
					for (int i = 0; i < m_nextPoolSize; i++)
						m_values.add(&pool[i]);

					// Increment pool size. The size is chosen to double the capacity on
					// each growth.
					m_nextPoolSize = capacity();
				}
			}
		}

		/** Returns the number of elements the container can hold before needing to
			allocate more memory. */
		int capacity()
		{
			return m_values.count();
		}

		/** Returns the element at "index". */
		T& operator[](int index)
		{
			return *m_values[index];
		}

		int count()
		{
			return m_count;
		}

	private:
		Array<T*> m_values;
		Array<T*> m_pools;
		int m_nextPoolSize;
		int m_count;

		#pragma region Iterator
	public:
		class Iterator
		{
		public:
			Iterator(StableArray* host, int index)
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
			T* operator->() const
			{
				return &(*m_host)[m_index];
			}

		private:
			StableArray* m_host;
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
}