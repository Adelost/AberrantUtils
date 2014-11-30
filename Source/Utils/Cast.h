#pragma once

namespace ae
{
	/** Utility class to make casting more convenient and helps prevent code
		duplication when implementing identical const and non-const methods.
		
		Const casting is generally to be avoided, as it destroys the intent of
		const correctness. However, one useful trick to avoid code duplication
		when creating an identical const and a non-const get method, is to call
		the const method from the non-const method.
		
		Example:
		<pre>
		Cast::removeConst(Cast::makeConst(this).someMethod());
		</pre>
		
		See "Avoid Duplication in const and Non-const Member Function" in
		"Effective C++" 3rd edition by Scott Meyers, for more information. */
	class Cast
	{
	public:
		/** Makes the inputed object const. */
		template<class T>
		static const T& makeConst(T& object)
		{
			return static_cast<const T&>(object);
		}
		template<class T>
		static const T* makeConst(T* object)
		{
			return static_cast<const T*>(object);
		}

		/** Removes const from inputed object. */
		template<class T>
		static T& removeConst(const T& object)
		{
			return const_cast<T&>(object);
		}
		template<class T>
		static T* removeConst(const T* object)
		{
			return const_cast<T*>(object);
		}
	};
}

/** Convenience macro to call a const method as a non-const method, see "Cast"-for further information. */
#define CALL_CONST_METHOD_AS_NON_CONST(CONST_METHOD) Cast::removeConst(Cast::makeConst(*this).CONST_METHOD)