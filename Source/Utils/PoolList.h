#pragma once

#include "Array.h"
#include "NativePoolArray.h"
#include "Math.h"

namespace ae
{
	/** Pool allocator */
	template<class T>
	class PoolList
	{
#pragma region NestedClasses
	private:
		struct Node
		{
			Node() {};
			Node(T value)
			{
				this->value = value;
				next = -1;
				prev = -1;
			}

			int next;
			int prev;
			T value;
		};
#pragma endregion

	public:
		PoolList()
		{
			init();
		}
		void init()
		{
			m_first = -1;
			m_last = -1;
		}
		void add(const T& value)
		{
			int index = s_nodes.add(Node(value));
			if (m_last == -1)
			{
				m_first = index;
				m_last = index;
			}
			else
			{
				s_nodes[index].prev = m_last;
				s_nodes[m_last].next = index;
				m_last = index;
			}
		}
		void clear()
		{
			int next = m_first;
			while (next != -1)
			{
				int prev = next;
				next = s_nodes[next].next;
				s_nodes.removeAt(prev);
			}
			init();
		}
		void clearPool()
		{
			s_nodes.clear();
			init();
		}

		class Iterator
		{
		public:
			Iterator(PoolList* list)
			{
				m_list = list;
				reset();
			}
			void reset()
			{
				m_next = m_list->m_first;
				m_current = -1;
			};
			bool hasNext()
			{
				return m_next != -1;
			}
			T next()
			{
				m_current = m_next;
				m_next = s_nodes[m_next].next;
				return s_nodes[m_current].value;
			}
			void remove()
			{
				if (m_current != -1)
				{
					// Fill gap
					int prev = s_nodes[current]->prev;
					if (prev == -1)
					{
						m_list->m_first = m_next;
					}
					else
					{
						s_nodes[prev].next = m_next;
					}
					if (m_next == -1)
					{
						m_list->m_last = prev;
					}
					else
					{
						s_nodes[m_next].prev = prev;
					}

					// Delete node
					s_nodes.removeAt(m_current);
				}
			}

		private:
			PoolList* m_list;
			int m_next;
			int m_current;
		};

		Iterator iterator()
		{
			return Iterator(this);
		}

	private:
		int m_first;
		int m_last;

		static NativePoolArray<Node> s_nodes;
	};

	template<class T>
	NativePoolArray<typename PoolList<T>::Node> PoolList<T>::s_nodes;
}


//
//
//
//struct Shared
//{
//	Shared()
//	{
//		firstFree = -1;
//		lastFree = -1;
//	}
//
//	/// Adds value and returns index where value was stored
//	int add(const T& value)
//	{
//		// Get a valid index to put element
//		int index = nextFreeIndex();
//		nodes[index] = value;
//
//		return index;
//	}
//
//	void remove(int index)
//	{
//		if (lastFree == -1)
//		{
//			firstFree = index;
//			lastFree = index;
//		}
//		else
//		{
//			nodes[lastFree].next = index;
//			lastFree = index;
//		}
//	}
//
//	/// Returns a valid index to put new elements
//	int nextFreeIndex()
//	{
//		// Recycle already free nodes or create
//		// a new node
//		int index = firstFree;
//		if (index == -1)
//		{
//			index = nodes.count();
//			nodes.add();
//			values.add();
//		}
//		else
//		{
//			// Remove node free list
//			int next = nodes[firstFree].next;
//			firstFree = next;
//
//			if (next == -1)
//				lastFree = -1;
//		}
//return index:
//	}
//
//	Array<Node> nodes;
//	Array<T> values;
//	int firstFree;
//	int lastFree;
//};