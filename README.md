# Utils
A collection of classes and utilities useful in general programming.

## Content
Overview of content.
* **Addons** - Features which may be added to a class, usually through inheritance.
    * Inspectable - Allows introspection of subclasses. Only supports introspection of member variables currently.
    * NonCopyable - Other classes can inherit from this class to disallow copying of the the
    class, e.g. "class SomeClass : private NonCopyable {};".
* **Libs** - Functions collected as static methods of various classes.
    * Algorithm - Facilitates algorithms, such as sorting.
    * Console - Makes writing console applications more convenient. Also allows outputting various classes using standard ostream
    * Cast - Utility class to make casting more convenient and helps prevent code duplication when implementing identical     const and non-const methods.
    * StringConvert - Facilitate strings conversion.
    * Format - Make formating strings easier.
    * Math - Math utility class.
    * Memory - Makes managing memory in an application more convenient.
    * Random - Randomization utility class.
    * Time - Utility class for managing time.
* **Misc** - Macros and defines.
    * XAssert - Custom assert macros. More safe than standard assert, and a prints a nicer call stack. 
    * DataTypes - Portable data types. 
    * CallOnce - Make sure code in input parameter is only run once.
    * DebugOnly - Make sure code is only run in debug or release.
    * IgnoreMemleak - Ignore all memory leaks caused by memory allocations within parenthesis.
    * StaticCall - Allows code to be called automatically during the start of the program. Only to be used in .cpp files.
* **Tools** - Various classes.
    * PoolAlloc - Allow fast allocation of objects. This is usually much faster than standard allocation using "new" and "delete".
    * Array - Dynamic array implementation. 
    * Queue - Array like FIFO-queue implementation. 
    * StableArray - Similar to a dynamic-array, but which do not reallocate the memory address of the stored elements when growing. However, elements are not guaranteed to be stored in adjacent memory locations.
    * PoolArray - A mix between a pool allocator and a dynamic array. Elements are stored based on a index.
    * IdPoolArray - Similar to PoolArray, but elements are stored based on a id as well as index.
    * PoolList - A mix between a linked list and a pool allocator. Faster to add and remove elements than in a ordinary linked list.
    * StopWatch - High-precision time measuring class.

## Introspection example

```cpp
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
````

## ToDo
* Implementing const iteratores.
* Reuse code between iteratores.
* Better categorization.
* Introspection of methods using lambda functions.
