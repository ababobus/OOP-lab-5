#include <iostream>
#include <string>

class Animal {
public:
    Animal() {
        std::cout << "Animal() constructor\n";
    }
    ~Animal() {
        std::cout << "~Animal() destructor\n";
    }
    virtual void sound() {
        std::cout << "virtual animal sound\n";
    }

    virtual std::string classname()
    {
        return "Animal";
    }
    virtual bool isA(const std::string &type)
    {
        if (type == "Animal")
        {
            return true;
        }
        return false;
    }



};

class Dog :public Animal {
public:
    Dog()
    {
        std::cout << ("Dog() constructor\n");
    }
    ~Dog()
    {
        std::cout << ("~Dog() destructor\n");
    }

    void sound() override {
        std::cout << "Gav-gav\n";
    }
    void chase_cat() {
        std::cout << "void catch mouse\n";
    }
    std::string classname() override
    {
        return "Dog\n";
    }
    bool isA(const std::string &type)
    {
        if (type == "Dog")
        {
            return true;
        }
        return Animal::isA(type);
    }
};

class Cat : public Animal {
public:
    Cat()
    {
        std::cout << ("Cat() constructor\n");
    }
    ~Cat()
    {
        std::cout << ("~Cat() destructor\n");
    }
    std::string classname() override
    {
        return "Cat\n";
    }
    void catch_mouse() {
        std::cout << "void catch mouse\n";
    }
    void sound() override {
        std::cout << "Me-mew\n";
    }
    bool isA(const std::string &type)
    {
        if (type == "Cat")
        {
            return true;
        }
        return Animal::isA(type);
    }
};

class Manul : public Cat {
public:
    std::string classname() override {
        return "Manul\n";
    }
    bool isA(const std::string& type) override {
        if (type == "Manul") {
            return true;
        }
        return Cat::isA(type);
    }
};


int main() {
    Animal* a1 = new Cat();//указатель на кошку, типа животного
    //a1->catch_mouse()
    //у животного нет метода catch mouse - можно воспользоваться небезопасным приведением типов
    //static_cast<Cat*>(a1)->catch_mouse();

    if (a1->isA("Cat")) {
        static_cast<Cat*>(a1)->catch_mouse();
    }


    Animal* a2 = new Manul();
    //a2->catch_mouse(); 
    Cat* c = dynamic_cast<Cat*>(a2);


    if (c != nullptr) {
        c->catch_mouse();//как Manul у потомка Cat вызовется - норм
    }
    delete a1;
    delete a2;//а2 указывает на Манул
    //сначала вызывается конструктор базового класса, потом потомка
    //когда удаляем объект потомка сначала вызывается деструктор потомка затем деструктор базового класса
    //для объекта Кошка будет вызван констр Животного и Кошки,
    //для объекта Манул констр Животное, Кошка, Манул
    //но при удалении а1 и а2 вызываются деструкторы Животного, которые автоматически вызовут деструкторы потомков


}