#include <iostream>
#include <type_traits>

namespace io {

template <typename T, typename = void>
struct has_ostream_op : std::false_type {};

template <typename T>
struct has_ostream_op<T,
                      std::void_t<decltype(std::cout << std::declval<T &>())>>
    : std::true_type {};

template <typename T, typename = void>
struct iterable_cout_able : std::false_type {};

template <typename T>
struct iterable_cout_able<T, std::void_t<decltype(std::declval<T &>().begin()),
                                         decltype(std::declval<T &>().end()),
                                         // without decay_t here, T is actually a reference when used in `print(T&&)`, ie T&
                                         // (because T&& signature in `print` when given a list/container deduces arg to a T&)
                                         // but to access ::value_type on `T`, it needs to be a non-reference type
                                         decltype(std::cout << std::declval<typename std::decay_t<T>::value_type>())>>
    : std::true_type {};

// 1.
template <typename T>
typename std::enable_if_t<has_ostream_op<T>{}> print(T &&t) {
  std::cout << std::forward<T>(t) << std::flush;
}

// 2.
template <typename T>
typename std::enable_if_t<
    std::conjunction_v<std::negation<decltype(has_ostream_op<T>{})>,
                       decltype(iterable_cout_able<T>{})>>
print(T &&t, const char* delim = "") {
  for (auto &&x : t)
    std::cout << std::forward<decltype(x)>(x) << delim;

  std::cout << "\n" << std::flush;
}

// 3.
template <bool start = true, typename T, typename... Ts>
void print(const char *delim, T &&first, Ts... rest) {
//  if (start) std::cout << "   ";
  std::cout << first << delim;

  return print(delim, rest...);
}
} // namespace io
