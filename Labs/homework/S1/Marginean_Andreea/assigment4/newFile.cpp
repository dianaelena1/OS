#include <iostream>

class Animal {
public:
    Animal() {}
};

class Dog {
public:
    Dog(int age) {}
};

class Cat {
public:
    Cat(std::string name) {}
};

int main() {
    Animal a1;               
    Animal* a2 = new Animal; 

    Dog d1(5);               
    Dog* d2 = new Dog(3);    

    Cat c1("Whiskers");      
    Cat* c2 = new Cat("Mittens"); 

    return 0;
}


