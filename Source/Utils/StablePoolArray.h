#pragma once

#include "PoolArrayBase.h"
#include "StableArray.h"

namespace ae
{
	template<class T>
	class StablePoolArray : public PoolArrayBase < T, StableArray<T> >
	{
	public:
		StablePoolArray() {}
		StablePoolArray(int capacity) : PoolArrayBase(capacity) {}
	};
}