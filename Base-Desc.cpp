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
        std::cout << "Base(const Base*obj) worked\n";
    }
    Base(const Base& obj) {
        this->value = obj.value;
        std::cout << "Base(const Base &obj) worked\n";
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
    void some_desc_method() {
        std::cout << "Desc::some method worked\n";
    }
};

void func1(Base obj) {
    obj.get_value();
    std::cout << __LINE__ << " " << "func1(Base * obj) worked\n";
}

void func2(Base* obj) {
    //obj->get_value();
    //obj->some_desc_method(); не сработает, можно привести тип
    Desc* c = dynamic_cast<Desc*>(obj);
    if (c != nullptr){ //действительно ли хранится по адресу объект Desc* ?
        c->some_desc_method();
        std::cout << __LINE__ << " " << "func2(Base *obj) with derived Desc object worked\n";
    }
    else {
        std::cout << __LINE__ << " " << "func2(Base *obj) with non-derived object worked\n";
    }
}

void func3(Base &obj) { 
    Desc* d = dynamic_cast<Desc*>(&obj);
    if (d != nullptr) {
        d->some_desc_method();
        std::cout << __LINE__ << " " << "func3(Base &obj) with derived Desc object worked\n";
    }
    else {
        std::cout << __LINE__ << " " << "func3(Base &obj) with non-derived object worked\n";
    }
}

Base func1_static() {
    Base o1;
    std::cout << "Base func1() static \n";
    return o1;
};

Base* func2_static() { 
    Base o2;
    std::cout << "Base func2() static \n";
    return &o2;
};
Base& func3_static() {
    Base o3;
    std::cout << "Base func3() static \n";
    return o3;
};
Base func4_dynamic() { 
    Base* o4 = new Base();
    std::cout << "Base func4() dynamic \n";
    return *o4;
};
Base* func5_dynamic() { 
    Base* o5 = new Base();
    std::cout << "Base func5() dynamic \n";
    return o5;
};

Base& func6_dynamic() { 
    Base* o6 = new Base();
    std::cout << "Base func6() dynamic \n";
    return *o6;
};



int main()
{    
    Base basePrimer;
    Desc descPrimer; //вызовется конструктор Base и Desc  
    Base* r = new Desc(); //неявный конструктор Base и конструктор Desc 
    //Desc::Desc(); можно так вызвать конкретный конструктор
    
    std::cout << "\n";
    std::cout << "3 void functions:\n";
    func1(basePrimer);
    func1(descPrimer); //передаем копию desc типа base

    func2(&basePrimer); //basePrimer не является объектом-потомком Desc
    func2(&descPrimer);
    func2(r); //r типа Base*, указывает на Desc

    func3(basePrimer);
    func3(descPrimer);

    std::cout<<"\n";
    //r->Base::get_value();
    
    std::cout << "6 Base*& functions:\n";
    Base o1 = func1_static();  
    o1.set_value(3);
    o1.get_value();

    Base* o2 = func2_static();
    o2->get_value();
    //delete o2; UB объект удалился в функции, удалять нечего

    Base &o3 = func3_static(); //возвращает ссылку на локальную переменную внутри функции
    o3.get_value();
    //delete &o3; UB объект удалился в функции, удалять нечего

    Base o4 = func4_dynamic();//локальный объект не удалится в функции, висит в памяти
    o4.set_value(99);
    o4.get_value(); 

    Base* o5 = func5_dynamic(); 
    o5->set_value(8);
    delete o5; //потенциальная утечка памяти

    Base& o6 = func6_dynamic(); //утечка памяти, надо delete&
    o6.set_value(34);
    o6.get_value();
    delete& o6;

    delete r;
    std::cout << "Hello World!\n";
    //ответственность на удалении указываемого объекта лежит на unique_ptr
    std::unique_ptr<Desc> unique_obj(new Desc());
    unique_obj->some_desc_method();
    unique_obj.reset();
    std::shared_ptr<Base> shared_obj(new Desc());
    shared_obj->set_value(12);
    shared_obj.reset();
}
