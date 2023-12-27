#include "Zoo.h"
#include "Animals.h"
#include <istream>
#include <fstream>
#include <random>
#include <map>

class AnimalCreator {

public:
	virtual ~AnimalCreator(){}

	// необходимо будет удалить память
	virtual Animal* create(const std::string& spec, const std::string name, int age) = 0;
};

class SimpleAnimalCreator:public AnimalCreator {

public:
	Animal* create(const std::string& spec, const std::string name, int age) override {
		if (spec == "Cow")
			return new Cow(name, age);

		if (spec == "Chicken")
			return new Chicken(name, age);

		if (spec == "Aligator")
			return new Aligator(name, age);

	}
};


class ZooCreator {

public:
	virtual ~ZooCreator() {}

	// необходимо будет удалить память
	virtual Zoo* Create() = 0;

};

class StreamZooCreator : public ZooCreator {
	std::istream& is;
	AnimalCreator* creator;

public:
	StreamZooCreator(std::istream& is, AnimalCreator* animal_creator) : is(is), creator(animal_creator){}

	Zoo* Create() override {
		Zoo* zoo = new Zoo();

		std::string spec, name;
		int age;

		while (is >> spec >> name >> age) {
			Animal* animal = creator->create(spec, name, age);
			if (animal) {
				zoo->addAnimal(animal);
			}
		}
		return zoo;
	}

};

class RandomZooCreator : public ZooCreator {
    AnimalCreator* creator;
    int numAnimals;

public:
    RandomZooCreator(int numAnimals, AnimalCreator* animal_creator) : numAnimals(numAnimals), creator(animal_creator) {}

    Zoo* Create() override {
        Zoo* zoo = new Zoo();

        std::ifstream namesFile("pet-names.txt");
        std::vector<std::string> names;

        std::string name;
        while (namesFile >> name) {
            names.push_back(name);
        }
        namesFile.close();

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> nameDist(0, names.size() - 1);
        std::uniform_int_distribution<> ageDist(1, 10);

        for (int i = 0; i < numAnimals; i++) {
            std::string randomName = names[nameDist(gen)];
            int randomAge = ageDist(gen);

            Animal* animal = creator->create("Random", randomName, randomAge);
            if (animal) {
                zoo->addAnimal(animal);
            }
        }

        return zoo;
    }
};

class PrototypedAnimalCreator : public AnimalCreator {
    std::map<std::string, Animal*> protoanimals;

public:
    void addProtoanimal(const std::string& spec, Animal* animal) {
        protoanimals[spec] = animal;
    }

    Animal* create(const std::string& spec, const std::string name, int age) override {
        if (protoanimals.count(spec) > 0) {
            Animal* protoanimal = protoanimals[spec];
            Animal* animal = protoanimal->clone();
            animal->set_name(name);
            animal->set_age(age);
            return animal;
        }
        else {
            return nullptr;
        }
    }
};