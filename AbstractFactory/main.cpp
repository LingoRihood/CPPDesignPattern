#include <iostream>
#include "AbstractFactory.h"

int main() {
    AbstractFactory* fac = nullptr;
    AbstractBall* ball = nullptr;
    AbstractShirt* shirt = nullptr;

    fac = new BasketballFactory();
    ball = fac->getBall();
    shirt = fac->getShirt();
    delete fac;
    delete ball;
    delete shirt;

    fac = new FootballFactory();
	ball = fac->getBall();
	shirt = fac->getShirt();
	delete fac;
	delete ball;
	delete shirt;

#ifdef win32
    system("pause");
#endif  
    return 0;
}