#pragma once

#include "Array.h"
#include "Field.h"

#include <string>
#include <map>

namespace ae
{
	class ClassInfo
	{
	public:
		ClassInfo();

		/** Returns name of the class. */
		std::string name();
		/** Returns field, or "nullptr" if field does not exist. */
		Field* field(char* name);

		void _init(std::string name);
		void _add(Field::Type type, void* member, std::string name);
		bool _hasInit();
		void _setTarget(void* target);
	
	private:
		bool m_init;
		void* m_target;
		std::string m_name;
		Array<Field> m_array;
		std::map<std::string, Field> m_map;

	public:
		#pragma region Iterator
		class Iterator
		{
		public:
			Iterator(ClassInfo* host, int index);
			void reset();
			bool operator!=(const Iterator& other) const;
			Field* operator*() const;
			const Iterator& operator++();

		private:
			ClassInfo* m_host;
			int m_index;
		};
		Iterator begin();
		Iterator end();
		#pragma endregion
	};
}