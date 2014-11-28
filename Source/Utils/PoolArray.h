#pragma once

#include "PoolArrayBase.h"

namespace ae
{
	template<class T>
	class PoolArray : public PoolArrayBase < T, Array<T> >
	{
	public:
		PoolArray() {}
		PoolArray(int capacity) : PoolArrayBase(capacity) {}
	};
}
