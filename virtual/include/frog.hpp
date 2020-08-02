#include "creature.hpp"

namespace Creature {

class Frog : public Creature {
public:
  using Creature::Creature;

  ~Frog() override { std::cout << "Frog destructor" << std::endl; }

private:
  void DoAttack() override {
    std::cout << name << " shoots a poison dart." << std::endl;
  }
};

} // namespace Creature
