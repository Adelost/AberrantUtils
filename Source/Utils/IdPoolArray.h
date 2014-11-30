#pragma once

#include "StablePoolArray.h"

namespace ae
{
	/** Similar to PoolArray, but elements are stored based on a id as well as index. */
	template<class T>
	class IdPoolArray
	{
	public:
		void clear()
		{
			PoolArray::clear();
			m_indices.clear();
		}

		T* add(int id, const T& value)
		{
			// Reuse previous index or allocate a new one
			int index = indexFromId(id);
			if (index = -1)
			{
				index = m_pool.add(value);

				// Increase capacity if necessary
				while (m_ids.count() < m_pool.count())
				{
					m_ids.addEmpty();
					m_gaps.addEmpty();
					m_enabled.addEmpty();
				}
			}

			m_ids[index] = id;
			m_gaps[index] = false;
			m_enabled[index] = true;

			// Save id to be able to retrieve values later
			while (id >= m_indices.count())
				m_indices.add(-1);
			m_indices[id] = index;

			return &m_pool[index];
		}

		int index(const T& value)
		{
			return static_cast<int>(&m_values[0] - &value);
		}
		int id(const T& value)
		{
			return  idFromIndex(index(value));
		}

		T* operator[](int index)
		{
			return valueFromId(index);
		}

		void removeAt(int id)
		{
			int index = indexFromId(id);
			if (index != -1)
			{
				// Remove value
				m_gaps[index] = true;
				m_enabled[index] = false;
				m_ids[id] = -1;
				m_count--;

				// Check if new first gap is needed
				if (index < m_firstGap)
					m_firstGap = index;

				// If value was next to last gap a new gap is needed
				if (index == m_lastGap - 1)
					findNextLastGap();
			}
		}

		int count()
		{
			return m_pool.count();
		}

		T* valueFromId(int id)
		{
			int index = indexFromId(id);
			if (index != -1)
				return &m_pool[index];

			return nullptr;
		}

		T* valueFromIndex(int index)
		{
			return &m_pool[index];
		}

		/** Returns the index belonging to an id, returns "-1" if no index exists. */
		int indexFromId(int id)
		{
			if (id < m_indices.count())
				return m_indices[id];
			return -1;
		}
		/** Returns id belonging to index, id typically represents owner of value
			stored at index. */
		int idFromIndex(int index)
		{
			return m_ids[index];
		}

	private:
		bool _isEnabled(int index) const
		{
			return m_enabled[index];
		}

		StablePoolArray<T> m_pool;
		Array<int> m_ids;
		Array<bool> m_enabled;
		Array<bool> m_gaps;
		Array<int> m_indices;

	public:
		#pragma region Iterator
		class Iterator
		{
		public:
			Iterator(IdPoolArray* target, int index)
			{
				m_target = target;
				m_index = index;
				_findNextElement();
			}
			void reset()
			{
				m_index = 0;
			}
			bool operator!=(const Iterator& other) const
			{
				return m_index < other.m_index;
			}
			T* operator*() const
			{
				return (*m_target).valueFromIndex(m_index);
			}
			const Iterator& operator++()
			{
				m_index++;
				_findNextElement();

				return *this;
			}

		private:
			void _findNextElement()
			{
				while (m_index < m_target->count() && !m_target->_isEnabled(m_index))
					m_index++;
			}

			int m_index;
			IdPoolArray* m_target;
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