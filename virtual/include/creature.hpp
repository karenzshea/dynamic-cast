#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <iostream>
#include <memory>
#include <string>

enum class Element {
  Wind = 1,
  Earth,
  Fire,
  Water,
  Music,
};

namespace Creature {

class Creature {
public:
  Creature(unsigned int _level, Element _element, std::string &&_name)
      : level(_level), element(_element), name(std::move(_name)){};

  virtual ~Creature() { std::cout << "Creature destructor" << std::endl; };

  void Attack() { DoAttack(); };

  int DamagePoints() { return CalculateDamagePoints(); }

  // getters
  const Element &getElement() const { return element; }
  const unsigned int &getLevel() const { return level; }
  const std::string &getName() const { return name; }

private:
  virtual void DoAttack() {
    std::cout << "Waves appendages threateningly." << std::endl;
  };

  virtual int CalculateDamagePoints() {
    return level + static_cast<unsigned int>(element);
  }

protected:
  unsigned int level;
  Element element;
  std::string name;
};

template <class T, class U>
auto *Fight(const T &creature1, const U &creature2) {
  creature1->Attack();
  creature2->Attack();

  if (creature1->DamagePoints() > creature2->DamagePoints()) {
    return &creature2;
  }
  return &creature1;
}

} // namespace Creature

#endif
