
#include "SystemSpec.h"

int main()
{
    int t{1};

    Star star(std::string("Sun"), 1.989e30, 696'340.0, Position(0,0));
    Planet planet(std::string("Earth"), 5.972e24, 696'340.0, Position(1,0), Velocity(1,1));

    std::cout << star;
    std::cout << planet;

    return 0;
}


