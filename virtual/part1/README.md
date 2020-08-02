# Virtual

## What is it

**`Virtual`** is the keyword used to indicate that a member function of a class may be overridden by derived classes.

When **derived classes** implement an **override** of a virtual method of their base class, the compiler can guarantee that the derived class’s version of the method will be called instead of the base class version. Virtual guarantees that the overridden version is called.[1](#fn1)

A class’s **destructor** should be declared `virtual` when that class is intended to be used as a base class. Declaring a **virtual destructor** ensures that any derived classes’ destructors will be called through a pointer to the base class. Otherwise, derived class may be sliced on destruction and result in memory leaking.[2](#fn2)

A simplified guideline: “A base class destructor should be either public and virtual (or maybe protected and nonvirtual).”[3](#fn3)

Pure virtual functions are `virtual` member functions with extra syntax like `= 0;`

```cpp
class A {
  virtual void Process() = 0;
};
```

The existence of one pure virtual member function in a class makes that class a **virtual base class**. A class with only pure virtual member functions is a **pure virtual base class**, or, an **interface**. Virtual base classes cannot be instantiated as is: they need to be inherited from and then have their pure virtual member functions implemented.[4](#fn4)

## Resources
https://isocpp.org/wiki/faq/virtual-functions#virtual-ctors
http://www.gotw.ca/publications/mill18.htm

### Footnotes:

<b id="fn1">1</b>
Show this in the example!
    - Remove `virtual` from one of the methods
    - remove `override` from the subclass methods.

<b id="fn2">2</b>
Show this in the example!
    - Either add a new derived creature with an extra data field, or add an extra data field to an existing class
    - Remove `virtual` from `Creature::~Creature()`

<b id="fn3">3</b>
[Link to guideline in core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c35-a-base-class-destructor-should-be-either-public-and-virtual-or-protected-and-non-virtual). Discuss the protected+nonvirtual part???

<b id="fn4">4</b>
Show this in the example!
    - Add an instance of `Creature::Creature` to `creatures_list`
    - Make one of the virtual methods pure virtual
