#include <cassert>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "creature.hpp"
#include "dragon.hpp"
#include "frog.hpp"

int main(int, char **) {
  std::unordered_map<std::string, std::unique_ptr<Creature::Creature>>
      creatures_list{};

  creatures_list.insert({"randall", std::make_unique<Creature::Dragon>(
                                        4, Element::Earth, "randall")});
  creatures_list.insert({"kermit", std::make_unique<Creature::Frog>(
                                       2, Element::Music, "kermit")});

  auto loser = Creature::Fight(creatures_list.at("randall"),
                               creatures_list.at("kermit"));

  creatures_list.erase((*loser)->getName());

  std::cout << "Game over.\n\n" << std::endl;
}
