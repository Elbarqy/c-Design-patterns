#ifndef BUILDER_PATTERN
#define BUILDER_PATTERN 
/*
@usage
	Builder* myBuilder = new typeABuilder();
	myBuilder->partA();
	myBuilder->partB();
	//in the next line the product is reset
	//new product is initilized
	Product* myprod = myBuilder->GetProduct();
	myprod->listParts();
	//we can use the new product in the director
	//apply the sequence and then add part A
	Director* boss = new Director();
	boss->set_builder(myBuilder);
	boss->buildSequence();
	myBuilder->partA();
	myprod = myBuilder->GetProduct();
	myprod->listParts();
*/
#include<iostream>
#include<vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Product {
	//simple item that only consists of list of strings
public:
	vector<string> parts;
	void listParts() const {
		const size_t partsSize = parts.size();
		auto backend = parts.back();
		for (size_t i = 0; i < partsSize; i++) {
			if (i == partsSize-1)
				cout << parts[i];
			else
				cout << parts[i] << ",";
		}
		cout << "\n\n";
	}
};

class Builder {
public:
	/*
	Making sure to initilize the destructor to avaiod any memory leaks
	Also Resetting the product within the builder is important
	to avoid re building over the produc itself
	*/
	virtual ~Builder() {};
	virtual void reset() {};
	virtual void partA() const = 0;
	virtual void partB() const = 0;
	virtual void partC() const = 0;
	virtual Product* GetProduct() { return NULL; };
};

class typeABuilder : public Builder{
private:
	Product* product;
	//you can add a flag for each part 
	//if you don't want the parts to be added more than once
	void reset() override {
		this->product = new Product();
	}
	~typeABuilder() { 
		delete product;
	}

public:
	//Basic construction of the product
	//This allows any permutation of the products to be added
	//and for this code can result in multiple addition of the product
	typeABuilder() {
		this->reset();
	}
	void partA() const override {
		this->product->parts.push_back("partA");
	}
	void partB() const override {
		this->product->parts.push_back("partB");
	}
	void partC() const override {
		this->product->parts.push_back("partC");
	}
	Product* GetProduct() {
		//the product will always remain within the builder untill it's requested
		//then the product is reset within the builder
		//this will enable the builder variable to be used more than once
		//no need for deleting the builder and recreating it
		Product* result = this->product;
		this->reset();
		return result;
	}
};

class Director {
	//this class will construct a sequence of actions on the builder
	//these actions will form the new standard object
	//without the need for constructing a new class
	//Multiple Directors can be applied on one builder
private:
	//this will take any builder using polymorphism
	//not just the typeABuilder
	Builder* builder;

public:
	void set_builder(Builder* passed_buillder) {
		this->builder = passed_buillder;
	}

	void buildSequence() {
		this->builder->partA();
		this->builder->partA();
		this->builder->partC();
		this->builder->partB();
	}

	~Director() {
		delete this->builder;
	}
};


#endif // !BUILDER_PATTERN


#pragma once
