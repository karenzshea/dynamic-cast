#include "template.hpp"

int main() {
    std::cout << std::boolalpha;
    Frog MusicFrog{3, Element::Music};
    Dragon Anna{5};
    Frog FireFrog{3, Element::Fire};

    Healer mage{1, Element::Music};

    std::cout << Fight(MusicFrog, Anna) << "\n";
    std::cout << Fight(MusicFrog, FireFrog) << "\n";
    std::cout << Fight(MusicFrog, mage) << "\n";
    std::cout << std::endl;
}
