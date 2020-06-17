#ifndef ABSTRACT_FACTORY
#define ABSTRACT_FACTORY
/*
usage
myFactory* fac = new myFactory();
auto prodA = fac->createProductA();
auto prodB = fac->createProductB();
std::cout << prodA->getName() << std::endl;
std::cout << prodB->getName() << std::endl;
*/

#include <iostream>

class Product {
protected:
	std::string name;
	virtual std::string getName() { return "myFactory"; };
};

class productA : Product {
private:
	std::string prodName;
public:
	productA(const std::string& passedName)
		: prodName(passedName) {}
	std::string getName() override { return prodName; };
};

class productB : public Product {
public:
	productB(const std::string passedName) {
		name = passedName;
	}
	std::string getName() override { return name; };
};

class myFactory {
public:
	productA *createProductA() {
		return new productA("ProductA created ");
	}
	productB *createProductB() {
		return new productB("ProductB created");
	}
};


#endif // !ABSTRACT_FACTORY
#pragma once
