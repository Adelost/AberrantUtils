#pragma once

#include "Random.h"

#include <algorithm>
#include <utility>

namespace ae
{
	/** Facilitates algorithms, such as sorting. */
	class Algorithm
	{
	public:
		/** Randomly rearranges the first "count" elements. */
		template<class T>
		static void shuffle(T* elements, int count);
		/** Sorts the first elements "count" elements in ascending order. */
		template<class T>
		static void sort(T* elements, int count);
		/** Like sort(), but also preserves the relative order of elements with
			equivalent values, at the cost of some performance. */
		template<class T>
		static void stableSort(T* elements, int count);
	};

	template<class T>
	void Algorithm::shuffle(T* elements, int count)
	{
		for (int i = 0; i < count; i++)
		{
			int rand = Random::nextUniform(count);
			std::swap(elements[i], elements[rand]);
		}
	}

	template<class T>
	void Algorithm::sort(T* elements, int count)
	{
		std::sort(elements, elements + count);
	}

	template<class T>
	void Algorithm::stableSort(T* elements, int count)
	{
		std::stable_sort(elements, elements + count);
	}
}