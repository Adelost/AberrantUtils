#pragma once

#include "ClassInfo.h"

#define INTROSPECT(NAME, MEMBERS) \
ae::ClassInfo& introspect() \
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

#define MEMBER(TYPE, VAR) \
	info._add(TYPE, &VAR, #VAR);

namespace ae
{
	/** Allows introspection of subclasses. */
	class Introspect
	{
	public:
		virtual INTROSPECT("Unkown", )
	};
}