#include "creature.hpp"

namespace Creature {

class Dragon : public Creature {
public:
  using Creature::Creature;

  ~Dragon() override { std::cout << "Dragon destructor" << std::endl; }

private:
  void DoAttack() override {
    std::cout << name << " breathes some fire." << std::endl;
  }
};

} // namespace Creature
