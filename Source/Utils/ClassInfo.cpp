#include "ClassInfo.h"

namespace ae
{
	ClassInfo::ClassInfo()
	{
		m_init = false;
	}

	void ClassInfo::_init(std::string name)
	{
		m_name = name;
		m_init = true;
	}

	void ClassInfo::_add(Member::Type type, void* member, std::string name)
	{
		int offset = (int)member - (int)m_target;
		Member d(&m_target, offset, type, name);

		m_array.add(d);
		m_map[name] = d;
	}

	bool ClassInfo::_hasInit()
	{
		return m_init;
	}

	std::string ClassInfo::name()
	{
		return m_name;
	}

	void ClassInfo::_setTarget(void* target)
	{
		m_target = target;
	}

	Member* ClassInfo::member(char* name)
	{
		auto it = m_map.find(name);
		if (it == m_map.end())
			return nullptr;
		Member* m = &it->second;
		return m;
	}

	ClassInfo::Iterator ClassInfo::begin()
	{
		return Iterator(this, 0);
	}

	ClassInfo::Iterator ClassInfo::end()
	{
		return Iterator(this, m_array.count());
	}

	ClassInfo::Iterator::Iterator(ClassInfo* host, int index)
	{
		m_host = host;
		m_index = index;
	}

	void ClassInfo::Iterator::reset()
	{
		m_index = 0;
	}

	bool ClassInfo::Iterator::operator!=(const Iterator& other) const
	{
		return m_index < other.m_index;
	}

	Member* ClassInfo::Iterator::operator*() const
	{
		return &m_host->m_array[m_index];
	}

	const ClassInfo::Iterator& ClassInfo::Iterator::operator++()
	{
		m_index++;

		return *this;
	}
}