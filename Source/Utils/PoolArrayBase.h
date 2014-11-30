#pragma once

#include "XAssert.h"
#include "Array.h"
#include <iostream>

namespace ae
{
	template<class T, class ELEMENT_ALLOCATOR>
	class PoolArrayBase
	{
	public:
		PoolArrayBase()
		{
			clear();
			m_capacity = 0;
		}

		PoolArrayBase(int size) : PoolArrayBase()
		{
			resize(size);
		}

		void clear()
		{
			m_firstGap = 0;
			m_lastGap = 0;
		}

		/** Adds a value to the container and returns the index where it was stored.
			The index should be saved and used to delete the element later on using
			remove(). */
		int add(const T& value)
		{
			reserve(m_lastGap + 1);
			int index = nextIndex();

			m_elements[index] = value;
			m_gaps[index] = false;

			// Check if new last gap is needed
			if (index == m_lastGap)
				m_lastGap++;

			return index;
		}

		void print()
		{
			_findFirstGap();

			for (int i = 0; i < m_elements.count(); i++)
			{
				if (i == m_firstGap)
					std::cout << "<";
				else if (i == m_lastGap)
					std::cout << ">";
				else if (isGap(i))
					std::cout << "-";
				else
					std::cout << m_elements[i];
			}
			std::cout << "\n";
		}

		void remove(int index)
		{
			//xassert_msg(!isGap(index), "Element is already removed. ");

			// Remove element
			m_gaps[index] = true;

			// Check if new first gap is needed
			if (index < m_firstGap)
				m_firstGap = index;

			// If index was next to last gap a new gap is needed
			if (index == m_lastGap - 1)
				_findLastGap();
		}

		int nextIndex()
		{
			// Find next gap
			_findFirstGap();

			return m_firstGap;
		}

		/** Returns element at index, do not use to iterate as the array may contain
			uninitialized elements; use the iterator instead. */
		T& operator[](int index)
		{
			return m_elements[index];
		}

		/** Returns the number of elements the container can hold before needing to
			allocate more memory. */
		int capacity()
		{
			return m_capacity;
		}

		void reserve(int size)
		{
			// Grow capacity if size exceeds capacity
			if (size > m_capacity)
			{
				if (m_capacity < 1)
					m_capacity = 1;
				while (m_capacity < size)
					m_capacity *= 2;

				m_elements.resize(m_capacity);
				m_gaps.resize(m_capacity);
			}
		}

		void resize(int size)
		{
			reserve(size);

			// Fill all empty gaps up to size
			m_lastGap = size;
			while (m_firstGap != m_lastGap)
			{
				int index = nextIndex();
				m_gaps[index] = false;
			}
		}

		/** Returns the number of valid indices held by the container. The number of
			indices is based on the number of stored elements, as well as potential
			gaps left over from removed elements. */
		int count() const
		{
			return m_lastGap;
		}

		/** Returns true if the container contains no elements. */
		bool isEmpty() const
		{
			return count() == 0;
		}

		/** Returns true if the index contains no element. */
		bool isGap(int index) const
		{
			return m_gaps[index];
		}


	private:
		void _findFirstGap()
		{
			// Step forward until a new gap is found or until end is reached
			while (m_firstGap < m_lastGap && !isGap(m_firstGap))
				m_firstGap++;
		}
		void _findLastGap()
		{
			// Step forward until a new gap is found or until beginning is reached
			while (m_lastGap > 0 && isGap(m_lastGap - 1))
				m_lastGap--;
		}

		ELEMENT_ALLOCATOR m_elements;
		Array<bool> m_gaps;
		int m_firstGap;
		int m_lastGap;
		int m_capacity;

	public:
		#pragma region Iterator
		class Iterator
		{
		public:
			Iterator(PoolArrayBase* target, int index)
			{
				m_target = target;
				m_index = index;
				findNextElement();
			}
			void reset()
			{
				m_index = 0;
			}
			bool operator!=(const Iterator& other) const
			{
				return m_index < other.m_index;
			}
			T& operator*() const
			{
				return m_target->m_elements[m_index];
			}
			const Iterator& operator++()
			{
				m_index++;
				findNextElement();

				return *this;
			}

		private:
			void findNextElement()
			{
				while (m_index < m_target->count() && m_target->isGap(m_index))
					m_index++;
			}

			int m_index;
			PoolArrayBase* m_target;
		};
		Iterator begin()
		{
			return Iterator(this, 0);
		}
		Iterator end()
		{
			return Iterator(this, count());
		}
		#pragma endregion
	};
}