#include <iostream>
#include <string>

class Base {
private:
    int value = 0;
public:
    void set_value(int value) {
        this->value = value;
    }
    Base() {
        std::cout << "Base constructor worked\n";
    }
    Base(const Base* obj) {
        this->value = obj->value;
        std::cout << "Base(Base*obj) worked\n";
    }
    Base(const Base& obj) {
        this->value = obj.value;
        std::cout << "Base(Base &obj) worked\n";
    }
    virtual ~Base() {
        std::cout << "virtual ~Base() worked\n";
    }
    virtual void get_value() {
        std::cout << "Base virtual get value worked, this->value: " << this->value << "\n";
    }
};

class Desc : public Base {
public:
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
        std::cout << "virtual~Desc() override worked\n";
    }
    virtual void get_value() override {
        std::cout << "Desc virtual get value worked\n";
    }
};

void func1(Base obj) {
    obj.get_value();
    std::cout << "func1(Base *obj) worked\n";
}

void func2(Base* obj) {
    //obj.get_value();
    if (dynamic_cast<Desc*>(obj)) {
        std::cout << "func2(Base *obj) with derived Desc object worked\n";
    }
    else {
        std::cout << "func2(Base *obj) with non-derived object worked\n";
    }
}

void func3(Base& obj) {
    //obj.get_value();
    if (dynamic_cast<Desc*>(&obj)) {
        std::cout << "func3(Base &obj) with derived Desc object worked\n";
    }
    else {
        std::cout << "func3(Base &obj) with non-derived object worked\n";
    }
}

Base func1_static() {//переполнение стека 
    Base o1;
    std::cout << "Base func1() static \n";
    return o1;
};

Base* func2_static() { //UB
    Base o2;
    std::cout << "Base func2() static \n";
    return &o2;
};

Base& func3_static() {//UB
    Base o3;
    std::cout << "Base func3() static \n";
    return o3;
};
Base func4_dynamic() { //утечка памяти
    Base* o4 = new Base();
    std::cout << "Base func4() dynamic \n";
    return *o4;
};
Base* func5_dynamic() { //мб утечка памяти, нужны умные указатели
    Base* o5 = new Base();
    std::cout << "Base func5() dynamic \n";
    return o5;
};
Base& func6_dynamic() { //утечка памяти, надо делет
    Base* o6 = new Base();
    std::cout << "Base func6() dynamic \n";
    return *o6;
};



int main()
{
    Base basePrimer;
    Desc descPrimer;

    basePrimer.set_value(5);
    descPrimer.set_value(9);

    func1(basePrimer);
    func1(descPrimer);

    func2(&basePrimer);
    func2(&descPrimer);

    func3(basePrimer);
    func3(descPrimer);

    //descPrimer->Base::get_value();

    Base o1 = func1_static(); 
    o1.set_value(3);
    o1.get_value();

    Base* o2 = func2_static();
    //o2->get_value();
    //delete o2; объект удалился в функции, удалять нечего


    Base &o3 = func3_static(); //возвращает ссылку на локальную переменную внутри функции
    //o3.get_value();
    //delete &o3; объект удалился в функции, удалять нечего

    Base o4 = func4_dynamic();
    o4.set_value(99);
    o4.get_value(); //не удалится в функции

    Base* o5 = func5_dynamic();
    o5->set_value(8);
    delete o5;

    Base& o6 = func6_dynamic();
    o6.set_value(34);
    o6.get_value();
    delete& o6;

    std::cout << "Hello World!\n";
}
