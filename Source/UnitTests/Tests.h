#pragma once

#define CATCH_CONFIG_RUNNER

#include <Catch/include/catch.hpp>
#include <Utils/Array.h>

using namespace ae;

TEST_CASE("Array")
{
	Array<int> a;
	a << 0 << 1 << 2 << 3 << 4;

	SECTION("add()")
	{
		REQUIRE(a.count() == 5);
		REQUIRE(a[0] == 0);
		REQUIRE(a[4] == 4);
	}

	SECTION("removeAt()")
	{
		a.removeAt(0);

		REQUIRE(a.count() == 4);
		REQUIRE(a[0] == 1);
		REQUIRE(a[3] == 4);
	}

	SECTION("addAt()")
	{
		a.addAt(0, -1);

		REQUIRE(a.count() == 6);
		REQUIRE(a[0] == -1);
		REQUIRE(a[5] == 4);
	}

	SECTION("Iterator")
	{
		int total = 0;
		for (int i : a)
			total += i;

		REQUIRE(total == 10);

		for (auto it = a.begin(); it != a.end(); ++it)
			total += *it;

		REQUIRE(total == 20);
	}
}

#include <Utils/StablePoolArray.h>

TEST_CASE("StablePoolArray")
{
	StablePoolArray<int> a;

	SECTION("add")
	{
		a.add(0);
		a.add(1);

		REQUIRE(a[1] == 1);

		a.add(2);
		a.remove(1);
		a.add(3);

		REQUIRE(a[1] == 3);
	}

	SECTION("Iterator")
	{
		a.add(1);
		a.add(2);
		a.add(3);

		int total = 0;
		for (int i : a)
			total += i;

		REQUIRE(total == 6);
	}
}

#include <Utils/IdPoolArray.h>

TEST_CASE("IdPoolArray")
{
	IdPoolArray<int> a;

	SECTION("add()")
	{
		REQUIRE(a[0] == nullptr);

		a.add(0, 0);

		REQUIRE(a[0]);
		REQUIRE(*a[0] == 0);

		a.add(0, 1);
		a.add(1, 1);
		a.add(2, 2);

		REQUIRE(*a[0] == 1);
		REQUIRE(*a[2] == 2);

		a.count();
	}

	SECTION("Iterator")
	{
		a.add(0, 1);
		a.add(1, 2);
		a.add(2, 3);

		int total = 0;

		for (auto i : a)
			total += *i;

		REQUIRE(total == 6);
	}
}