Type traits are a way for developers to define certain functionality based on
compile-time evaluated type properties, i.e. introspection. Apparently concepts
in c++20 will make a lot of this kind of metaprogramming much, much simpler, but
they are somewhat still in progress.

# contents
1. [integral constant](#integral_constant)
2. [partial template specialization](#partial_template_specialization)
3. void_t
4. decltype/declval
5. enable_if


# resources
- https://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming/
- https://akrzemi1.wordpress.com/2017/12/02/your-own-type-predicate/
- #include discord metaprogramming channel

# 1. integral constant
Base class for many type traits.

## member constants and values

```c++
template<typename T, T v>
std::integral_constant
{
    typedef T value_type; // nested type, can be accessed for introspection
    T value;                      // actual value held
};
```

## boolean convenience helpers
```c++
// helpers that hold `value_type` of boolean, with `true` or `false` in `value`.
template <bool B>
using bool_constant = integral_constant<bool, B>;

// pseudo
struct true_type<bool> : integral_constant
{
    typedef T bool;
    bool value = true;
}
```

These types are helper classes for other classes to inherit or derive from, so
that user-defined types may "evaluate" to boolean type-value at compile time.

# 2. partial template specialization
One way to nudge the SFINAE process in a certain direction. In the base case of
`has_ostream_type`, the second template parameter is `void`. In the specialization
of `has_ostream_type` that inherits from `true`, the second template parameter
will still evaluate to void...but only when `void_t` has been passed valid type(s).
We don't care what that type actually is in this case, only that it's valid!
The `is_iterable` trait does the same thing, with a more complex trait.

## parameters vs arguments
Similar to a function params vs args. In context of functions these are often used
interchangeably, but with templates difference is important.

template parameters: canonically, `T`, `U` and so on. The generic type in the
template definition that the compiler looks at while performing type substitution.
```
template <typename T, typename U>
struct Dummy {...};
```

template arguments: The actual types passed in by the user to a template instantiation,
or in template specialization.
```
Dummy<int, UserType> dummy{...};
```

## 3. std::void_t
std::void_t is a helper metafunction that takes a variable number of template
arguments, and will either evaluate to `void` when all template arguments are
valid types, or evaluate to a type system error. This kind of error is OK by
SFINAE rules, it just tells the compiler to move on to the next template to try.

# 4. decltype/declval
`decltype` returns `type` of expression inside, useful for metafunctions requiring types.
> Note that if the name of an object is parenthesized, it is treated as an ordinary lvalue expression, thus decltype(x) and decltype((x)) are often different types. 


`declval` can be usefully used in template argument contexts. It allows you to
access the interface (methods or member constants and values) of a type, when
accessing those parts of the interface require a de-referencable instance of the type.
(And a note on the need for the `decay` inside `is_iterable` because, weird! a
remove_reference inside of an add reference??)

> Converts any type T to a reference type, making it possible to use member functions in decltype expressions without the need to go through constructors. 

# 5. std::enable_if
You can use `enable_if` to cleverly "turn on/off" template functions based on properties of the template arguments. 

```c
template< bool B, class T = void >
struct enable_if;
```
> If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef. 

By default, the result type of a `true` enable_if is `void`. If you want a different type, that is the second template argument. That result type is the return type of the enabled function.

How it works:
```c++
template<bool B>
std::enable_if
{
    // nothing! important.
};

std::enable_if<true>
{
    // partial specialization for `true` case
    typedef void type;
};
```

By default, enable_if evaluates to a struct type that does not have typedef `type`, i.e. a type system error.
But when the condition passed in as a template argument is `true`, the typedef to `type` exists and is valid.
Template arguments are passed into `enable_if` and evaluated to either true or false. And conveniently, type traits that inherit either from `std::true_type` or `std::false_type` can be used as template arguments to `enable_if`!

# notes
## note on suffix `_t`, and `_v`
A lot of the library metafunctions include convenience methods that return certain
traits so that you don't need to do func<T>::type or func<T>::value

## std::is_same

```c
template <typename T, typename U>
struct is_same : std::false_type {};

static_assert();
std::enable_if<>();
```
this `is_same` class has inherited the member `value`, accessed as `is_same::value`
from `std::false_type`. So when it is accessed at compile time it will evaluate to `false`.
It is a templated class with a `boolean` type, equal to value `false`, and two other types T and U.

We can make `is_same` compile-time evaluate to the `true_type` by using partial
template specialization. The base template of `is_same` has two types, T and U, but
we can specialize it for cases when it's created with two types, that happen to be the same.

```c
template<typename T>
struct<T, T> is_same : std::true_type {};
```

So two types are still required to instantiate `is_same`, we are just specializing
for when those types happen to be the same type. This exploits template argument
deduction rules which will select the base case for when two different types are
provided, and will select the specialized case for when two of the same types are provided.
Though they are the same class, `is_same`, the two cases are very different because
one derives from `false_type` and the other `true_type`.

```c
static_assert(is_same<int, char>::value, "Not the same types"); // will throw
static_assert(is_same<int, int>::value, "Not the same types"); // will not throw
```

## note on decay_t

On type trait `iterable_cout_able`:
// without decay_t here, T is actually a reference when used in `print(T&&)`, ie T&
// (because T&& signature in `print` when given a list/container deduces arg to a T&)
// but to access ::value_type on `T`, it needs to be a non-reference type

## note on typename keyword

`typename` keyword is a way to tell the compiler that you are referring to a type
that is part of a class, (a nested type, a subtype) not a member variable.
https://stackoverflow.com/questions/8073052/using-a-templated-parameters-value-type

```c
// without `typename` here, compiler would assume you are accessing a member var called `type`, which is also accessed like `enable_if<C>::type`.

template <bool Cond>
using enable_if_t = typename enable_if<Cond>::type;
```

