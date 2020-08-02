#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <type_traits>

template <typename T, typename = void>
struct iterable_cout_able : std::false_type {};

template <typename T>
struct iterable_cout_able<T, std::void_t<decltype(std::declval<T &>().begin()),
                                         decltype(std::declval<T &>().end()),
                                         decltype(std::cout << std::declval<typename std::decay_t<T>::value_type>())>>
    : std::true_type {};

template <typename T>
typename std::enable_if_t<iterable_cout_able<T>::value>
print(T &&t, const char* delim = "") {
  for (auto const &x : t)
    std::cout << x << delim;

  std::cout << "\n" << std::flush;
}

int main() {
    std::list<std::string> list{"hello", "world"};
    std::string str{"hello world"};

    std::cout << std::boolalpha << iterable_cout_able<decltype(list)>::value << std::endl;

    static_assert(iterable_cout_able<decltype(str)>::value, "not iterable cout able");
//    static_assert(iterable_cout_able<decltype((list))>::value, "not iterable cout able");
//    static_assert(iterable_cout_able<std::list<std::vector<double>>>(), "not iterable cout able");
//    print(list, " ");
    print(str);
    return 0;
}
