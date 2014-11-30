#pragma once

#include "PoolArrayBase.h"

namespace ae
{
	/** A mix between a pool allocator and a dynamic array. Elements are stored based on a index. */
	template<class T>
	class PoolArray : public PoolArrayBase<T, Array<T>>
	{
	public:
		PoolArray() {}
		PoolArray(int capacity) : PoolArrayBase(capacity) {}
	};
}
