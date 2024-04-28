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

    virtual std::string classname()
    {
        return "Animal";
    }
    virtual bool isA(std::string type)
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
        std::cout<<("Dog() constructor\n");
    }
    ~Dog()
    {
        std::cout<<("~Dog() destructor\n");
    }
    std::string classname() override
    {
        return "Dog";
    }
    bool isA(std::string type)
    {
        if (type == "Dog")
        {
            return true;
        }
        return Animal::isA(type);
    }
};

class Cat : public Animal{
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
        return "Cat";
    }
    bool isA(std::string type)
    {
        if (type == "Cat")
        {
            return true;
        }
        return Animal::isA(type);
    }
};


int main() {

}