#include <array>
#include <iostream>
#include <string>

namespace err
{
template <typename T> void print(T const &&t) {
  std::cout << std::forward<T>(t) << std::flush;
}

template <typename T> void print(T const &&t) {
  for (auto const &x : t)
    std::cout << x;

  std::cout << "\n" << std::flush;
}
}
