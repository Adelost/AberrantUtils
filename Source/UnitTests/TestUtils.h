#pragma once

#define CATCH_CONFIG_RUNNER

#include "Catch.h"


#include <Utils/Array.h>

using namespace ae;

TEST_CASE("Array") {
  Array<int> a;
  a << 0 << 1 << 2 << 3 << 4;

  SECTION("add()") {
    REQUIRE(a.count() == 5);
    REQUIRE(a[0] == 0);
    REQUIRE(a[4] == 4);
  }

  SECTION("removeAt()") {
    a.removeAt(0);

    REQUIRE(a.count() == 4);
    REQUIRE(a[0] == 1);
    REQUIRE(a[3] == 4);
  }

  SECTION("addAt()") {
    a.addAt(0, -1);

    REQUIRE(a.count() == 6);
    REQUIRE(a[0] == -1);
    REQUIRE(a[5] == 4);
  }

  SECTION("Iterator") {
    int total = 0;
    for (int i : a) {
      total += i;
    }

    REQUIRE(total == 10);

    for (auto it = a.begin(); it != a.end(); ++it) {
      total += *it;
    }

    REQUIRE(total == 20);
  }
}

#include <Utils/StablePoolArray.h>

TEST_CASE("StablePoolArray") {
  StablePoolArray<int> a;

  SECTION("add") {
    a.add(0);
    a.add(1);

    REQUIRE(a[1] == 1);

    a.add(2);
    a.remove(1);
    a.add(3);

    REQUIRE(a[1] == 3);
  }

  SECTION("Iterator") {
    a.add(1);
    a.add(2);
    a.add(3);

    int total = 0;
    for (int i : a) {
      total += i;
    }

    REQUIRE(total == 6);
  }
}

#include <Utils/IdPoolArray.h>

TEST_CASE("IdPoolArray") {
  IdPoolArray<int> a;

  SECTION("add()") {
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

  SECTION("Iterator") {
    a.add(0, 1);
    a.add(1, 2);
    a.add(2, 3);

    int total = 0;

    for (auto i : a) {
      total += *i;
    }

    REQUIRE(total == 6);
  }
}

#include <Utils/PoolAlloc.h>

TEST_CASE("PoolAlloc") {
  Array<PoolAlloc<int>> a;
  a << 0 << 1 << 2 << 3 << 4;

  int total = 0;
  for (PoolAlloc<int> i : a) {
    total += *i;
  }

  REQUIRE(total == 10);

  for (PoolAlloc<int> i : a) {
    i.release();
  }
}

#include <Utils/Format.h>

TEST_CASE("string formatting") {
  SECTION("maches found") {
    std::string s;

    s = Format::string("%1, %2, %4, %3, %1")
      % "text"
      % 42
      % 3.14f
      % true;

    REQUIRE(s == "text, 42, true, 3.14, text");
  }

  SECTION("no matches found") {
    std::string s;

    s = Format::string("")
      % "text";

    REQUIRE(s == "");

    s = Format::string("%a %b %c")
      % "text";

    REQUIRE(s == "%a %b %c");
  }
}

#include <Utils/Inspectable.h>

class MyInspectableClass : Inspectable {
public:
  INSPECTABLE(
    "MyInspectableClass",
    FIELD(Field::Int, m_int, "MyInt")
    FIELD(Field::Bool, m_bool, "MyBool")
    FIELD_AUTONAMED(Field::Float, m_float)
  );

  MyInspectableClass() {
    m_int = 42;
    m_bool = true;
    m_float = 3.14f;
  }

private:
  int m_int;
  bool m_bool;
  float m_float;
};

TEST_CASE("introspection") {
  MyInspectableClass i;

  REQUIRE(i.inspect().name() == "MyInspectableClass");
  REQUIRE(i.inspect().field("MyBool")->valueAsString() == "true");
  REQUIRE(i.inspect().field("m_float")->valueAsString() == "3.14");

  Field* m = i.inspect().field("MyInt");

  REQUIRE(m->valueAsString() == "42");
  REQUIRE(m->typeName() == "Int");
  REQUIRE(m->type() == Field::Int);
  REQUIRE(m->value<int>() == 42);

  std::string values;
  for (Field* m : i.inspect()) {
    values += m->valueAsString() + " ";
  }

  REQUIRE(values == "42 true 3.14 ");
}

