#include <cstdlib>
#include <iostream>

enum class Element {
    Wind = 1,
    Earth,
    Fire,
    Water,
    Music,
};

struct Creature {
    virtual ~Creature() {};
    Creature(unsigned int _level, Element _element)
        : level(_level), element(_element) {};
    virtual void Attack() = 0;

    unsigned int level;
    Element element;
};

struct Frog : Creature {
    Frog(unsigned int _level, Element element)
        : Creature(_level, element) {};

    void Attack() {
        std::cout << "shoots poison dart" << std::endl;
    }
};

struct Dragon : Creature {
    Dragon(unsigned int _level)
        : Creature(_level, Element::Fire) {};

    void Attack() {
        std::cout << "breathes some fire" << std::endl;
    }
};

// TODO implement a Creature

struct Healer {
    unsigned int level;
    Element element;
};

template<class T, class U>
bool Fight(T &creature1, U &creature2) {
    std::cout << "template is called" << std::endl;
    creature1.Attack();
    creature2.Attack();

    // very complicated game logic
    return creature1.level + static_cast<unsigned int>(creature1.element)
        > creature2.level + static_cast<unsigned int>(creature2.element);
}

//template<>
bool Fight(Frog const &frog1, Frog const &frog2) {
    std::cout << "overload is called" << std::endl;
    // special logic for frog fights
    return std::rand() % 2 == 0;
}

