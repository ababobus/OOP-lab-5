#include <iostream>
#include <string>

class Base {
private:
    int num = 0;
public:
    void set_num(int num) {
        this->num = num;
    }
    int get_num() {
        return this->num;
    }
    Base(int num) {
        this->num = num;
        std::cout << "Base(int num) constructor worked\n";
    }

    Base() {
        std::cout << "Base constructor worked\n";
    }
    Base(const Base* obj) {
        std::cout << "Base(Base*obj) worked\n";
    }
    Base(const Base& obj) {
        std::cout << "Base(Base &obj) worked\n";
    }
    virtual ~Base() {
        std::cout << "virtual ~Base() worked\n";
    }
};

class Desc : public Base {
    Desc(int num) : Base(num) {
        std::cout << "Desc(int num) worked\n";
    }

    Desc() {
        std::cout << "Decs constructor worked\n ";
    }
    Desc(Desc* obj) {
        std::cout << "Desc(Desc *obj) worked\n";
    }

    Desc(Desc& obj) {   
        std::cout << "Desc(Desc &obj) worked\n";
    }

    virtual ~Desc() override {
        std::cout << "~Desc() override worked\n";
    }
};

void func1(Base obj) {
    obj.set_num(obj.get_num() + 1);
    std::cout << "func1(Base *obj) worked\n";
}

void func2(Base* obj) {
    obj->set_num(obj->get_num()+1);
    std::cout << "func2(Base *obj) worked\n";
}

void func3(Base& obj) {
    obj.set_num(obj.get_num() + 1);
    std::cout << "func3(Base &obj) worked\n";
}

int main()
{
    Base* basePrimer = new Base(10);
    Desc* descPrimer = new Desc(5);

    func1(basePrimer);
    func1(descPrimer);

    func2(basePrimer);
    func2(descPrimer);

    func3(*basePrimer);
    func3(*descPrimer);

    //descPrimer->Base::get_num();

    std::cout << "Hello World!\n";
}
