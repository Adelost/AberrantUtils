#pragma once

#include "Array.h"
#include "Member.h"

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
		/** Returns member, or "nullptr" if member does not exist. */
		Member* member(char* name);

		void _init(std::string name);
		void _add(Member::Type type, void* member, std::string name);
		bool _hasInit();
		void _setTarget(void* target);
	
	private:
		bool m_init;
		void* m_target;
		std::string m_name;
		Array<Member> m_array;
		std::map<std::string, Member> m_map;

	public:
		#pragma region Iterator
		class Iterator
		{
		public:
			Iterator(ClassInfo* host, int index);
			void reset();
			bool operator!=(const Iterator& other) const;
			Member* operator*() const;
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