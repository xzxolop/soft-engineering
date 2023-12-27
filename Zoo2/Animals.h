#pragma once
#include <iostream>
#include <string>
#include <ostream>

class Animal {

	virtual void print(std::ostream& os) const = 0;

public:
	Animal() {
		std::cout << "Animal is born";
	}

	virtual std::string say() const = 0;

	virtual std::string move() = 0;

	virtual ~Animal() {
		std::cout << "Animal is died" << std::endl;
	}

	virtual void set_name(std::string n) = 0;

	virtual void set_age(int a) = 0;

	friend std::ostream& operator<<(std::ostream& os, Animal const& a) {
		a.print(os);
		return os;
	}

	virtual Animal* clone() = 0;


};


class Mammal : public Animal {};
class Bird : public Animal {};
class Reptile: public Animal{};

template<typename T>
class Creature :public T {
	int age;
	std::string name;

	void print(std::ostream& os) const override {
		os << "Name: " << get_name() << ", age: " << get_age();
	}

public:

	int get_age() const {
		return age;
	}

	std::string get_name() const {
		return name;
	}

	void set_name(std::string n) override {
		name = n;
	}

	void set_age(int a) override {
		age = a;
	}

	Creature(const std::string& name, int age): name(name), age(age){}

};

class Cow : public Creature<Mammal> {
	
public:
	Cow(const std::string& name, int age): Creature<Mammal> (name,age){
		std::cout << " - Cow is born" << std::endl;
	}

	virtual std::string say() const override {
		return "Muuuu";
	}

	std::string move() override {
		return "Top top";
	}

	Animal* clone() override {
		return new Cow(*this);
	}

	~Cow() {
		std::cout << "Cow is died - ";
	}
};



class Chicken : public Creature<Bird> {

public:
	Chicken(std::string const& name, int age): Creature<Bird>(name, age){
		std::cout << " - Chicken is born" << std::endl;
	}

	virtual std::string say() const override {
		return "kur kur";
	}

	std::string move() override {
		return "top top";
	}

	Animal* clone() override {
		return new Chicken(*this);
	}

	~Chicken() {
		std::cout << "Chicken is died - ";
	}
};


class Aligator : public Creature<Reptile> {

public:
	Aligator(std::string const& name, int age): Creature<Reptile>(name,age) {
		std::cout << " - Aligator is born" << std::endl;
	}

	virtual std::string say() const override {
		return "Arrrr";
	}

	std::string move() override {
		return "Top Top";
	}

	Animal* clone() override {
		return new Aligator(*this);
	}

	~Aligator() {
		std::cout << "Aligator is died - ";
	}
};

