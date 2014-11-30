#pragma once

#include "ClassInfo.h"

#define INSPECTABLE(NAME, MEMBERS) \
ae::ClassInfo& inspect() \
{ \
	static ae::ClassInfo info; \
	info._setTarget(this); \
	if (!info._hasInit()) \
				{ \
		info._init(NAME); \
		MEMBERS \
				} \
	return info; \
}

#define MEMBER(TYPE, VAR, NAME) \
	info._add(TYPE, &VAR, NAME);

#define MEMBER_AUTONAMED(TYPE, VAR) \
	info._add(TYPE, &VAR, #VAR);

namespace ae
{
	/** Allows introspection of subclasses. Only supports introspection of
		member variables currently. */
	class Inspectable
	{
	public:
		virtual INSPECTABLE("Unkown", )
	};
}