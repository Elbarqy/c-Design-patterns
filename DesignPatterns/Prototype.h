#ifndef PROTOTYPE_PATTERN
#define PROTOTYPE_PATTERN

#include<iostream>
#include <unordered_map>
using std::string;
using std::cout;
using std::endl;

enum Type {
    PROTOTYPE_1 = 0,
};

class Prototype {
protected:
    string prototype_name_;
    float prototype_field_;

public:
    Prototype() {}
    Prototype(string prototype_name)
        : prototype_name_(prototype_name) {
    }
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float prototype_field) {
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field : " << prototype_field << std::endl;
    }
};


class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_;

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field) {
    }
    Prototype* Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;

public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
    }

    ~PrototypeFactory() {
        delete prototypes_[Type::PROTOTYPE_1];
    }

    Prototype* CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};


#endif // !PROTOTYPE_PATTERN
#pragma once
