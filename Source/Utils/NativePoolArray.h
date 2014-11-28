#pragma once

#include "Array.h"
#include "Math.h"
#include "XAssert.h"

namespace ae
{
	/** Container structure that provides pool-based allocation of elements. It is
		useful when fast allocation and deallocation of elements is needed. Adding
		and removing elements is O(1) average and O(n) worst case.

		It works by the same principle as a pool allocator. Same size elements are
		allocated in a preallocated memory block. The structure is traversed
		linearly, as an array, as compared to a more common linked list approach. An
		iterator is needed to traverse the values stored inside, as the array may
		contain gaps. */
	template<class T>
	class NativePoolArray
	{
	public:
		NativePoolArray()
		{
			clear();
		}
		void clear()
		{
			m_count = 0;
			m_firstGap = 0;
			m_lastGap = 0;
		}

		/** Adds a value to the container and returns the index where it was
			stored. */
		int add(const T& value)
		{
			// Add element, reuse gaps if any
			int index = nextIndex();
			xassert_msg(index <= capacity(),
				"Index is larger than capacity, this should never happen.");
			if (index == capacity())
			{
				m_values.resize(m_values.count() + 1);
				m_gaps.resize(m_gaps.count() + 1);
			}
			m_values[index] = value;
			m_gaps[index] = false;
			m_count++;

			// Find next gap
			findNextGap();

			return index;
		}

		void reserve(int size)
		{
			m_values.reserve(size);
			m_gaps.reserve(size);
		}

		void removeAt(int index)
		{
			if (!isGap(index))
			{
				// Remove value
				m_gaps[index] = true;
				m_count--;

				// Check if new first gap is
				// needed
				if (index < m_firstGap)
					m_firstGap = index;

				// If value was next to last gap
				// a new gap is needed
				if (index == m_lastGap - 1)
				{
					findNextLastGap();
				}
			}
		}

		int nextIndex()
		{
			return m_firstGap;
		}

		/** Returns element at index, do not use to iterate as the array may
			contain uninitialized elements; use the iterator instead. */
		T& operator[](int index)
		{
			return m_values[index];
		}

		/** Returns the number of elements the container can hold before needing
			to allocate more memory. */
		int capacity()
		{
			return m_values.count();
		}

	protected:
		bool isGap(int index)
		{
			return m_gaps[index];
		}

		void findNextGap()
		{
			// Step forward until new gap is found or until end is reached.
			m_firstGap++;
			while (m_firstGap < m_lastGap && !isGap(m_firstGap))
			{
				m_firstGap++;
			}

			if (m_lastGap < m_firstGap)
				m_lastGap = m_firstGap;
		}

		void findNextLastGap()
		{
			m_lastGap--;
			while (m_lastGap > 0 && isGap(m_lastGap - 1))
			{
				m_lastGap--;
			}
		}

		Array<T> m_values;
		Array<bool> m_gaps;

		int m_firstGap;
		int m_lastGap;

		int m_count;

#pragma region Iterator
	public:
		class Iterator
		{
		public:
			Iterator(NativePoolArray* target, int index)
			{
				m_target = target;
				m_index = index;
				ignoreGaps();
			}
			void reset()
			{
				m_index = 0;
			}
			bool operator!=(const Iterator& other) const
			{
				return m_index < other.m_index;
			}
			T& operator*()
			{
				return m_target->m_values[m_index];
			}
			const T& operator*() const
			{
				return m_target->m_values[m_index];
			}
			const Iterator& operator++()
			{
				m_index++;
				ignoreGaps();

				return *this;
			}

		private:
			void ignoreGaps()
			{
				while (m_index < m_target->m_lastGap && m_target->isGap(m_index))
				{
					m_index++;
				}
			}

			int m_index;
			NativePoolArray* m_target;
		};
		Iterator begin()
		{
			return Iterator(this, 0);
		}
		Iterator end()
		{
			return Iterator(this, m_lastGap);
		}
#pragma endregion
	};
}