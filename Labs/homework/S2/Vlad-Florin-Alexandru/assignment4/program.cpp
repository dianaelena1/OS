#include <iostream>
using namespace std;

class Car {
public:
    Car() {}
};

class Animal {
public:
    Animal() {}
};

class Book {
public:
    Book() {}
};

int main() {
    Car myCar;
    Car* otherCar = new Car();

    Animal dog;
    Animal* cat = new Animal();

    Book b1;
    Book b2;

    return 0;
}
