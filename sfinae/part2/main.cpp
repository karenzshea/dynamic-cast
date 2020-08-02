#include <array>
#include <list>
#include <string>
#include <vector>

#include "trait_print.h"
//#include "template_print.h"

class NonIterable {
public:
  std::vector<int> data;
  double value;
};

int main() {
  std::string str = "hello world string\n";
  std::array<std::string, 4> arr{"hello", "world", "array"};
  std::vector<std::string> vec{"hello", "world", "vector"};
  std::list<std::string> list{"hello", "world", "list"};
  const char h{'h'};
  const double Double{2.0};

  io::print(h);
  io::print("\n");
  io::print(Double);
  io::print("\n");
  io::print(str);
  static_assert(io::iterable_cout_able<std::array<std::string, 4>>(), "iterable");
  io::print(arr, " ");
  io::print(vec, " ");
  io::print(list, " ");
  io::print(arr);

  io::print(" ", "hello", "world", "variadic", "\n");
  io::print("after hello world");

  NonIterable noniter{{1, 2, 3}, 3.0};

  /*
  // error message 1
  io::print(noniter);

  // error message 2
  std::vector<NonIterable> vec2{std::move(noniter)};
  io::print(vec2);
  */

  return 0;
}
