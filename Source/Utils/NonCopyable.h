#pragma once

/** Other classes can inherit from this class to disallow copying of the the
    class, e.g. "class SomeClass : private NonCopyable {};". */
class NonCopyable
{
private:
	NonCopyable(const NonCopyable& other) {}
	NonCopyable& operator=(const NonCopyable& other)
	{
		return *this;
	}

public:
	NonCopyable() {}
};