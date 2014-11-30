#pragma once

namespace ae
{
	/** Array like queue implementation. */
	template<class T>
	class Queue
	{
	public:
		Queue();
		Queue(int capacity);
		~Queue();
		void init();
		void clear();
		void clearCapacity();

		void add(T value);
		T next();

		T& operator[](int index);
		const T& operator[](int index) const;
		int count();
		bool isEmpty();

	private:
		void grow();

		T* m_values;
		int m_front;
		int m_back;
		int m_count;
		int m_capacity;
	};

	template<class T>
	Queue<T>::Queue()
	{
		init();
	}

	template<class T>
	Queue<T>::Queue(int capacity)
	{
		init();
		m_capacity = capacity;
		m_values = new T[capacity];
	}

	template<class T>
	Queue<T>::~Queue()
	{
		clearCapacity();
	}

	template<class T>
	void Queue<T>::init()
	{
		m_values = nullptr;
		m_count = 0;
		m_capacity = 0;
		m_front = 0;
		m_back = -1;
	}

	template<class T>
	void Queue<T>::add(T value)
	{
		// Expand capacity if needed
		if (m_count + 1 > m_capacity)
			grow();

		m_back++;

		// Wrap index to beginning if needed
		if (m_back >= m_capacity)
			m_back = 0;

		m_values[m_back] = value;
		m_count++;
	}

	template<class T>
	T Queue<T>::next()
	{
		T value = m_values[m_front];
		m_front++;

		// Wrap index to beginning if needed
		if (m_front >= m_capacity)
			m_front = 0;

		m_count--;
		return value;
	}

	template<class T>
	void Queue<T>::clear()
	{
		m_count = 0;
	}

	template<class T>
	void Queue<T>::clearCapacity()
	{
		delete[] m_values;
		init();
	}

	template<class T>
	T& Queue<T>::operator[](int index)
	{
		// Offset index relative to memory layout.
		// The queue needs to be able to "wrap" to
		// accommodate the "front" offset.
		index = m_front + index;
		if (index > m_capacity - 1)
			index -= m_capacity;
		return m_values[index];
	}

	template<class T>
	const T& Queue<T>::operator[](int index) const
	{
		index = m_front + index;
		if (index > m_capacity - 1)
			index -= m_capacity;
		return m_values[index];
	}

	template<class T>
	int Queue<T>::count()
	{
		return m_count;
	}

	template<class T>
	bool Queue<T>::isEmpty()
	{
		return m_count <= 0;
	}

	template<class T>
	void Queue<T>::grow()
	{
		// Determine new capacity
		m_capacity *= 2;
		if (m_capacity < 1)
			m_capacity = 1;

		// Transfer old data to new array
		T* tmp = new T[m_capacity];
		for (int i = 0; i < m_count; i++)
			tmp[i] = (*this)[i];

		delete[] m_values;
		m_values = tmp;

		m_front = 0;
		m_back = m_count - 1;
	}
}