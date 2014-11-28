#pragma once

namespace ae
{
	/** Utility class to make managing memory in an application more convenient. */
	class Memory
	{
	public:
		/** Makes binary copies of "count" elements from source to destination.
			To avoid overflows, the memory blocks should not overlap (for
			overlapping memory blocks, move() is a safer approach). */
		template<class T>
		static void copy(const T* source, T* destination, int count);
		/** Same as copy(), but copies bytes instead of whole elements. */
		static void copyRaw(const void* source, void* destination, int bytes);
		/** Similar to copy(), but allows source and destination to overlap. */
		template<class T>
		static void move(const T* source, T* destination, int count);
		/** Same as move() but copies bytes instead of whole elements. */
		static void moveRaw(const void* source, void* destination, int bytes);
		/** Allows memory leaks to be detected. */
		static void enableLeakDetection();
		/** Allocate a uninitialized block of memory big enough to contain
			"count" elements. Caller is responsible for freeing the memory
			later. */
		template<class T>
		static T* allocateRaw(int count);
		/** Deallocates memory block without calling any destructor. */
		static void deallocateRaw(void* data);
		/** Constructs an object on already allocated memory. Same as a
			"placement new". */
		template<class T>
		static void place(const T& object, T& destination);
	};

	template<class T>
	void Memory::copy(const T* source, T* destination, int count)
	{
		copyRaw(source, destination, count * sizeof(T));
	}

	template<class T>
	void Memory::move(const T* source, T* destination, int count)
	{
		moveRaw(source, destination, count * sizeof(T));
	}

	template<class T>
	T* Memory::allocateRaw(int count)
	{
		return static_cast<T*>(operator new[](count * sizeof(T)));
	}

	template<class T>
	void Memory::place(const T& object, T& destination)
	{
		new(&destination)T(object);
	}
}