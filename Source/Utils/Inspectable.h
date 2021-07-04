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

#define FIELD(TYPE, VAR, NAME) \
	info._add(TYPE, &VAR, NAME);

#define FIELD_AUTONAMED(TYPE, VAR) \
	info._add(TYPE, &VAR, #VAR);

namespace ae
{
	/** Allows introspection of subclasses. Only supports introspection of
		field variables currently. */
	class Inspectable
	{
	public:
		virtual INSPECTABLE("Unkown", )
	};
}
