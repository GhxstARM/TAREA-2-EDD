#include <iostream>
#include <string>

int main() {
    std::string nombre1 = "2";
    std::string nombre2 = "1";

    if (nombre1 < nombre2) {
        std::cout << nombre1 << " va antes que " << nombre2 << " en orden alfabético." << std::endl;
    } else {
        std::cout << nombre2 << " va antes que " << nombre1 << " en orden alfabético." << std::endl;
    }

    return 0;
}
