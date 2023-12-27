#pragma once
#include <vector>
#include "Animals.h"

class Zoo {
	std::vector<Animal*> animals;

public:

	void addAnimal(Animal* a) {
		animals.push_back(a->clone());
	}

	Zoo() {	};

	Zoo(const Zoo& z) = delete;

	Zoo& operator=(const Zoo& z) = delete;

	

	~Zoo() {
		for (int i = 0; i < animals.size(); i++) {
			delete animals[i];
		}
	}

	void walk() {
		for (auto x : animals) {
			std::cout << x->move() << ' ' << x->say() <<std::endl;
		}
	}
};


