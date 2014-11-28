#pragma once

#include "StablePoolArray.h" 
#include "XAssert.h" 

namespace ae
{
	/** Template class to allow fast allocation of objects. Objects should be
		instantiated with the class similarly to using a smart pointer. */
	template<class T>
	class PoolAlloc
	{
	public:
		PoolAlloc() {}

		PoolAlloc(const T& object)
		{
			set(object);
		}

		void set(const T& object)
		{
			int index = s_pool.add(object);
			m_index = index;
		}

		void release()
		{
			s_pool.remove(m_index);
		}

		T& get()
		{
			return s_pool[m_index];
		}

		T* operator->()
		{
			return &get();
		}

		T& operator*()
		{
			return get();
		}

		/** Preallocate memory for "size" number of elements to make allocation
			faster. */
		static void Reserve(int size)
		{
			s_pool.reserve(size);
		}

	private:
		class Allocator : public StablePoolArray < T >
		{
		public:
			~Allocator()
			{
				xassert_msg(s_pool.isEmpty(),
					"Some elements allocated by PoolAlloc has not been released.");
			}
		};
		static Allocator s_pool;
		int m_index;
	};

	template<class T>
	typename PoolAlloc<T>::Allocator PoolAlloc<T>::s_pool;
}